#include"ViewManager.h"
#include"../Device/Device.h"
#include"../SingletonTemplate/SingletonTemplate.h"





bool ViewManager::CreateRenderTargetView(
	const std::string& view_name
) {

	// すでに登録されているなら
	if (mp_render_target_view_list.count(view_name) != 0) {
		return false;
	}

	/*
	RenderTargetは
	レンダリングパイプラインからアウトプットされる
	ピクセル情報を保存するView
	このViewの内容をゲーム画面に反映させる
	*/

	ComPtr<ID3D11Texture2D>back_buffer;

	HRESULT hr;

	// RenderTargetViewの対象となるBufferの取得
	hr =
		Singleton<Device>::GetInstance()->GetPtrSwapChain()
		->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(LPVOID*)&back_buffer
		);

	if (hr != S_OK) {
		return false;
	}

	// BufferからRenderTargetViewの作成
	hr = Singleton<Device>::GetInstance()->GetPtrDevice()
		->CreateRenderTargetView(
			back_buffer.Get(),
			NULL,
			&mp_render_target_view_list[view_name]
		);

	if (hr != S_OK) {
		return false;
	}

	// Targetの取得が終わったのでBufferを解放
	// カウンタが1加算されているため
	// Releaseを行わないとメモリリークを起こす
	back_buffer->Release();

	return true;
}


bool ViewManager::CreateClientSizeDepthStencilView(
	const std::string& window_class_name
) {

	HWND w_handle =
		FindWindowA(window_class_name.c_str(), nullptr);

	if (w_handle == nullptr) {
		return false;
	}

	RECT rect;
	// クライアント領域取得
	GetClientRect(w_handle, &rect);

	D3D11_TEXTURE2D_DESC tex_desc;

	// デスク設定
	{
		// メモリを初期化
		ZeroMemory(&tex_desc, sizeof(D3D11_TEXTURE2D_DESC));

		tex_desc.Width = (rect.right - rect.left);
		tex_desc.Height = (rect.bottom - rect.top);


		/*
			ミップマップのレベル指定
				どのレベルまで生成するかという設定
				1はマルチサンプリングされたテクスチャを使用するあるので、
				ミップマップはなしと考えられる
				0は全生成とあるので可能な限りのレベルまでテクスチャが生成されると思われる
		*/
		tex_desc.MipLevels = 1;

		/*
		テクスチャ配列のサイズ指定
		テクスチャ配列について調べ切れていないので
		他のサンプルと同様に1を設定しておく
		*/
		tex_desc.ArraySize = 1;

		/*
		テクスチャのフォーマット
		DXGI_FORMAT_D24_UNORM_S8_UINTを使用する
		これはおそらくDepth24bit、Stencil8bitとされると思う

		※．UNORMはUnsigned NORMalizedの略で指定された範囲を0.0～1.0にするみたい

		*/
		// テクスチャフォーマット
		tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

		// マルチサンプリング設定(使わない)
		tex_desc.SampleDesc.Count = 1;
		tex_desc.SampleDesc.Quality = 0;
		// テクスチャの使用方法(デフォルト)
		tex_desc.Usage = D3D11_USAGE_DEFAULT;
		// Bind設定はDepth、Stencilに設定
		tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		/*
			リソースへのCPUのアクセス権限についての設定
				ReadとWriteがあるが、権限について現状は考える必要はないはずなので、
				デフォルト値であると思われる0をしておく

				※．readとwriteはenum(D3D11_CPU_ACCESS_FLAG)で用意されていた

		*/
		tex_desc.CPUAccessFlags = 0;
		/*
			リソースオプションのフラグ
				Microsoft Docsでフラグを確認する限りは
				通常使用でフラグを設定する必要はないと思われるので
				0としておく
		*/
		tex_desc.MiscFlags = 0;
	}


	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;

	// デプスステンシルビューデスク設定
	{

		ZeroMemory(&dsv_desc, sizeof(dsv_desc));

		// フォーマット
		dsv_desc.Format =
			tex_desc.Format;

		/*
			DSVが何次元であるかとTextureの種類を設定する値
				D3D11_DSV_DIMENSION_TEXTURE2Dのほかにも
				D3D11_DSV_DIMENSION_TEXTURE1Dや
				D3D11_DSV_DIMENSION_TEXTURE2D_ARRAYなどがあったので
				DSVが何次元であるかとTextureの種類を設定するメンバと思われる
				今回は何も通常のTextureとして用意しているはず
				なので、D3D11_DSV_DIMENSION_TEXTURE2Dを指定
		*/
		dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsv_desc.Texture2D.MipSlice = 0;


	}

	// 作成
	CreateDepthStencilView(
		DEVICE_RENDER_TARGET_VIEW,
		tex_desc,
		dsv_desc
	);

	return true;
}


bool ViewManager::CreateDepthStencilView(
	const std::string& view_name,
	const D3D11_TEXTURE2D_DESC&tex_desc,
	const D3D11_DEPTH_STENCIL_VIEW_DESC &dsv_desc
) {

	if (mp_depth_stencil_texture_list.count(view_name) != 0) {
		return false;
	}

	if (mp_depth_stencil_view_list.count(view_name) != 0) {
		return false;
	}

	HRESULT hr;

	// tex_descの情報でテクスチャを作成
	hr = Singleton<Device>::GetInstance()->GetPtrDevice()->
		CreateTexture2D(
			&tex_desc,
			NULL,
			&mp_depth_stencil_texture_list[view_name]
		);

	if (hr != S_OK) {
		return false;
	}

	// CreateTexture2Dとdsv_descからDepthとStencilバッファを作る
	hr = Singleton<Device>::GetInstance()->GetPtrDevice()->
		CreateDepthStencilView(
		// DSVとして使用されるTexture
		mp_depth_stencil_texture_list[view_name].Get(),
		// DSVの設定
		&dsv_desc,
		// D3D11DepthStencilViewの出力先
		&mp_depth_stencil_view_list[view_name]
	);

	if (hr != S_OK) {
		return false;
	}

	return true;
}


void ViewManager::DestoryRenderTargetView(const std::string& view_name) {

	// 探す
	decltype(mp_render_target_view_list)::iterator it =
		mp_render_target_view_list.find(view_name);

	// endが帰ってきていないなら見つかった
	if (it != mp_render_target_view_list.end()) {

		mp_render_target_view_list[view_name]->Release();
		mp_render_target_view_list.erase(it);
	}

}


void ViewManager::DestoryDepthStencilView(const std::string& view_name) {


	// 探す
	decltype(mp_depth_stencil_view_list)::iterator it =
		mp_depth_stencil_view_list.find(view_name);

	// endが帰ってきていないなら見つかった
	if (it != mp_depth_stencil_view_list.end()) {

		mp_depth_stencil_view_list[view_name]->Release();
		mp_depth_stencil_view_list.erase(it);
	}
}


void ViewManager::DestoryDepthStencilTexture(
	const std::string& view_name
) {
	// 探す
	decltype(mp_depth_stencil_texture_list)::iterator it =
		mp_depth_stencil_texture_list.find(view_name);

	// endが帰ってきていないなら見つかった
	if (it != mp_depth_stencil_texture_list.end()) {

		mp_depth_stencil_texture_list[view_name]->Release();
		mp_depth_stencil_texture_list.erase(it);
	}
}



void ViewManager::Release() {

	for (auto v : mp_render_target_view_list) {
		v.second->Release();
	}

	mp_render_target_view_list.clear();

	for (auto v : mp_depth_stencil_view_list) {
		v.second->Release();
	}

	mp_depth_stencil_view_list.clear();

	for (auto v : mp_depth_stencil_texture_list) {
		v.second->Release();
	}

	mp_depth_stencil_texture_list.clear();
}


ComPtr<ID3D11RenderTargetView> ViewManager::GetPtrRenderTargetView(
	const std::string& view_name
) {
	return mp_render_target_view_list[view_name];
}


ComPtr<ID3D11DepthStencilView> ViewManager::GetPtrDepthStencilView(
	const std::string& view_name
) {
	return mp_depth_stencil_view_list[view_name];
}


ComPtr<ID3D11Texture2D> ViewManager::GetPtrDepthStencilTexture(
	const std::string& view_name
) {
	return mp_depth_stencil_texture_list[view_name];
}
