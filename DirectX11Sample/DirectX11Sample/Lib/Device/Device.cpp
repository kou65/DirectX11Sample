#include"Device.h"
#include"../Window/Window.h"


bool Device::Init(
	const std::string& window_class_name,
	bool is_window_mode
) {

	// ウィンドウモード代入
	m_is_window_mode = 
		is_window_mode;

	// DeviceとSwapChainの作成
	if (CreateDeviceAndSwapChain(
	window_class_name
	) == false) {
		return false;
	}

	// RenderTargetViewの作成
	if (CreateRenderTargetView() == false){
		return false;
	}

	// Depth,StencilViewの作成
	if (CreateDepthAndStencilView(
		window_class_name
	) == false) {
		return false;
	}

	// ビューポート設定
	if (SetUpViewPort(
	window_class_name
	) == false) {
		return false;
	}

	// シェーダー作成

	return true;
}


void Device::Release() {

	/* 
	   Release関数を呼びAddRefされて加算されていた
	   参照カウンタを減算
	*/

	if (mp_immediate_context != nullptr)
	{
		mp_immediate_context->ClearState();
		mp_immediate_context->Release();
	}

	if (mp_swap_chain != nullptr)
	{
		mp_swap_chain->Release();
	}

	if (mp_device != nullptr)
	{
		mp_device->Release();
	}

	if (mp_render_target_view != nullptr) {
		mp_render_target_view->Release();
	}

	if (mp_depth_stencil_view != nullptr) {
		mp_depth_stencil_view->Release();
	}

	if (mp_depth_stencil_texture != nullptr) {
		mp_depth_stencil_texture->Release();
	}
}


void Device::StartRendering() {

	float clear_color[4] = 
	{ 0.f,0.f,1.f,1.f };

	// RenderTargetViewのクリア
	mp_immediate_context->ClearRenderTargetView(
		mp_render_target_view,
		clear_color
	);

	// DepthViewとStencilViewのクリア
	mp_immediate_context->ClearDepthStencilView(
		mp_depth_stencil_view,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.f,
		0
	);
}


void Device::EndRendering() {


	// バッファを切り替える
	mp_swap_chain->Present(
		// 垂直同期のタイミング
		0,
		// 出力オプション
		0
	);
}


bool Device::CreateDeviceAndSwapChain(
const std::string&window_class_name
){

	DXGI_SWAP_CHAIN_DESC desc;


	if (SetUpDXGIParameter(
		window_class_name.c_str(), desc) == false) {
		return false;
	}

	HRESULT hr = NULL;

	// enum classではないので警告
	D3D_FEATURE_LEVEL level;

	hr = D3D11CreateDeviceAndSwapChain(
		// ビデオアダプタ指定(nullptrは既定)
		nullptr,
		// ドライバのタイプ(ハードウェア)
		D3D_DRIVER_TYPE_HARDWARE,
		// D3D_DRIVE_TYPE_SOFTWARE指定時に使用
		nullptr,
		// ランタイムレイヤーのフラグ指定(デバッグ時はD3D11_CREATE_DEVICE_DEBUGを指定)
		0,
		// D3D_FEATURE_LEVEL指定で自分で定義した配列を指定可能
		nullptr,
		// 上のD3D_FEATURE_LEVEL指定で自分で定義した配列を指定可能
		0,
		// SDKバージョン
		D3D11_SDK_VERSION,
		// デスク
		&desc,
		// 関数成功時のSwapChainの出力
		&mp_swap_chain,
		// 関数成功時のDeviceの出力
		&mp_device,
		// 成功したD3D_FEATURE_LEVELの出力先
		&level,
		// 関数成功時のContextの出力先
		&mp_immediate_context
	);

	if (hr != S_OK) {
		return false;
	}

	return true;
}


bool Device::SetUpDXGIParameter(
	const std::string& window_class_name,
	DXGI_SWAP_CHAIN_DESC& out_dxgi) {

	// 登録されているウィンドウハンドルを探して取得
	HWND w_handle =
		FindWindowA(
			window_class_name.c_str(),
			nullptr);

	if (w_handle == nullptr) {
		return false;
	}

	RECT rect;

	// クライアント領域取得(ウィンドウの枠の仲、描画枠)
	GetClientRect(w_handle,&rect);

	/*
		DirectX11版PresentationParameter
			バッファの数やサイズ、カラーフォーマット等を設定する
	*/
	ZeroMemory(&out_dxgi, sizeof(DXGI_SWAP_CHAIN_DESC));
	// バッファの数
	out_dxgi.BufferCount = 1;									  
	//バッファの横幅(クライアントサイズに合ったサイズにする)
	out_dxgi.BufferDesc.Width = (rect.right - rect.left);	  
	// バッファの縦幅
	out_dxgi.BufferDesc.Height = (rect.bottom - rect.top);  
	// カラーフォーマット
	out_dxgi.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	  
	// リフレッシュレートの分母
	out_dxgi.BufferDesc.RefreshRate.Numerator = 60;			      
	// リフレッシュレートの分子
	out_dxgi.BufferDesc.RefreshRate.Denominator = 1;			  
	// バッファの使い方 Usage => 使用方法
	out_dxgi.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	      
	// 出力対象のウィンドウハンドル
	out_dxgi.OutputWindow = w_handle;						      
	// マルチサンプリングのサンプル数(未使用は1)
	out_dxgi.SampleDesc.Count = 1;				  
	// マルチサンプリングの品質(未使用は0)
	out_dxgi.SampleDesc.Quality = 0;							  
	// ウィンドウモード指定(フル = true ノットフル = false)
	out_dxgi.Windowed = m_is_window_mode;	

	return true;
}


bool Device::CreateRenderTargetView() {

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
	mp_swap_chain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(LPVOID*)&back_buffer
	);

	if (hr != S_OK) {
		return false;
	}

	// BufferからRenderTargetViewの作成
	hr =
	mp_device->CreateRenderTargetView(
		back_buffer.Get(),
		NULL,
		&mp_render_target_view
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


bool Device::CreateDepthAndStencilView(
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

	// 深度ステンシルバッファ作成
	D3D11_TEXTURE2D_DESC tex_desc;

	// メモリを初期化
	ZeroMemory(&tex_desc, sizeof(D3D11_TEXTURE2D_DESC));

	// デスクサイズ
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

	HRESULT hr;

	// tex_descの情報でテクスチャを作成
	hr = mp_device->CreateTexture2D(
		&tex_desc,
		NULL,
		&mp_depth_stencil_texture
	);
	
	if (hr != S_OK) {
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;

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

	// CreateTexture2Dとdsv_descからDepthとStencilバッファを作る
	hr = mp_device->CreateDepthStencilView(
		// DSVとして使用されるTexture
		mp_depth_stencil_texture,
		// DSVの設定
		&dsv_desc,
		// D3D11DepthStencilViewの出力先
		&mp_depth_stencil_view
	);

	if (hr != S_OK) {
		return false;
	}

	return true;
}


bool Device::SetUpViewPort(
	const std::string& window_class_name
) {

	HWND w_handle = 
		FindWindowA(window_class_name.c_str(), nullptr);

	if (w_handle == nullptr) {
		return false;
	}

	RECT rect;

	GetClientRect(w_handle, &rect);

	float w = static_cast<float>(
		(rect.right - rect.left));
	float h = static_cast<float>(
		(rect.bottom - rect.top));

	//ビューポートの設定
	D3D11_VIEWPORT view_port;
	view_port.TopLeftX = 0;							   // 左上X座標
	view_port.TopLeftY = 0;							   // 左上Y座標
	view_port.Width = w;                // 横幅
	view_port.Height = h;
	                   // 縦幅
	view_port.MinDepth = 0.0f;						   // 最小深度
	view_port.MaxDepth = 1.0f;						   // 最大深度

	mp_immediate_context->RSSetViewports(
		1,					// 設定するビューポートの数
		&view_port);		// 設定するビューポート情報のポインタ

	return true;
}


void Device::SetViewPort(const D3D11_VIEWPORT& port) {

	mp_immediate_context->RSSetViewports(
		1,					// 設定するビューポートの数
		&port);		// 設定するビューポート情報のポインタ

	return;
}


bool Device::CreateDeferredContext() {

	ComPtr<ID3D11DeviceContext> p_def;

	mp_device->CreateDeferredContext(0,&p_def);

	p_def->Release();

	return true;
}


ID3D11DeviceContext *Device::GetPtrImmContext(){
	return mp_immediate_context;
}


ID3D11Device *Device::GetPtrDevice(){
	return mp_device;
}


IDXGISwapChain *Device::GetPtrSwapChain(){
	return mp_swap_chain;
}


ID3D11DepthStencilView *Device::GetPtrDepthStencilView() {
	return mp_depth_stencil_view;
}


ID3D11RenderTargetView *Device::GetPtrRenderTargetView() {
	return mp_render_target_view;
}
