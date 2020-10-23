#include"PrimitiveRenderer.h"
#include"../Device/Device.h"
#include"../SingletonTemplate/SingletonTemplate.h"



PrimitiveRenderer::PrimitiveRenderer() {

}


bool PrimitiveRenderer::Init() {


	mp_vs = std::make_unique<VertexShader>();
	mp_ps = std::make_unique<PixelShader>();

	// バーテックスシェーダー作成
	if (
		mp_vs->Create(
			Device::GetInstance()->GetPtrDevice(),
			"Lib/Shader/CSO/VertexShader.cso"
		) == false) {
		return false;
	}

	// ピクセルシェーダー作成
	if (
		mp_ps->Create(
			Device::GetInstance()->GetPtrDevice(),
			"Lib/Shader/CSO/PixelShader.cso"
		) == false) {
		return false;
	}

	return true;
}


void PrimitiveRenderer::RenderingPolygonDev(
	PolygonPrimitive* pol
) {

	RenderingPolygon(
		Device::GetInstance()->GetPtrImmContext(),
		Device::GetInstance()->GetPtrRenderTargetView(),
		Device::GetInstance()->GetPtrDepthStencilView(),
		pol
	);
}


void PrimitiveRenderer::RenderingPolygon(
	ID3D11DeviceContext*p_context,
	ID3D11RenderTargetView*p_render_target,
	ID3D11DepthStencilView*p_depth_stencile,
    PolygonPrimitive* pol
) {

	// ポリゴンの描画で必要なことは
	// 適切な情報をGPU側に送信すること

	UINT strides = pol->GetCustomVertexSize();

	UINT offsets = 0;

	ID3D11Buffer* buff = 
		pol->GetVertexBuffer().GetBuffer();


	// 描画で使用する入力レイアウトを設定する
	p_context->IASetInputLayout(
		pol->GetPtrInputLayout().Get()
	);

	// レンダリングパイプラインで描画する頂点バッファを指定する
	p_context->IASetVertexBuffers(
		// 入力スロットの開始番号
		0,
		// 頂点バッファの数
		1,
		// 頂点バッファの配列
		&buff,
		// 1頂点のサイズの配列
		&strides,
		// 頂点バッファの開始位置をずらすオフセットの配列
		&offsets
	);

	// プリミティブの種類を設定する
	p_context->IASetPrimitiveTopology(
		pol->GetPrimitive()
	);

	// バーテックスシェーダーをセットする
	p_context->VSSetShader(
		mp_vs->GetInterfacePtr(),
		NULL,
		0
	);

	// ピクセルシェーダーをセットする
	p_context->PSSetShader(
		mp_ps->GetInterfacePtr(),
		NULL,
		0
	);

	// 描画処理の出力先ビューの設定
	p_context->OMSetRenderTargets(
		1,
		&p_render_target,
		p_depth_stencile
	);

	// 頂点描画
	p_context->Draw(
		pol->GetVertexCount(), // 頂点の数
		pol->GetStartVertex()  // 頂点バッファの描画開始インデックス
	);
}


void PrimitiveRenderer::RenderingMesh(
	ID3D11DeviceContext* p_context,
	ID3D11RenderTargetView* p_render_target,
	ID3D11DepthStencilView* p_depth_stencile,
	MeshPrimitive* mesh
) {


	UINT strides = 
		mesh->GetCustomVertexSize();

	UINT offsets = 0;

	// 描画で使用する入力レイアウトを設定する
	p_context->IASetInputLayout(
		mesh->GetPtrInputLayout().Get()
	);


	// バーテックスシェーダーをセットする
	p_context->VSSetShader(
		mp_vs->GetInterfacePtr(),
		NULL,
		0
	);

	// ピクセルシェーダーをセットする
	p_context->PSSetShader(
		mp_ps->GetInterfacePtr(),
		NULL,
		0
	);

	// 描画処理の出力先ビューの設定
	p_context->OMSetRenderTargets(
		1,
		&p_render_target,
		p_depth_stencile
	);

	ID3D11Buffer* p_buf =
		mesh->GetVertexBuffer().GetBuffer();

	// バーテックスバッファのセット
	p_context->IASetVertexBuffers(
		0, 1, &p_buf, &strides, 
		&offsets
	);

	ID3D11Buffer* p_ibuf =
		mesh->GetIndexBuffer().GetBuffer();

	// インデックスバッファのセット
	p_context->
		IASetIndexBuffer(
			p_ibuf,
			DXGI_FORMAT_R16_UINT,
			0
		);

	// 形状描画
	p_context->
		IASetPrimitiveTopology(
			mesh->GetPrimitive()
		);

	// 配列描画
	p_context->DrawIndexed(
		(mesh->GetIndexCount()),
		0, 
		0
	);

}


void PrimitiveRenderer::RenderingMeshDev(
	MeshPrimitive* mesh
) {

	RenderingMesh(
		Device::GetInstance()->GetPtrImmContext(),
		Device::GetInstance()->GetPtrRenderTargetView(),
		Device::GetInstance()->GetPtrDepthStencilView(),
		mesh
	);
}


void PrimitiveRenderer::SetUpRasterizer() {
	D3D11_RASTERIZER_DESC rdc = { };
	// 塗りつぶすかどうかを決める
	rdc.FillMode = D3D11_FILL_SOLID;
	// 面の描画ルールを決める
	rdc.CullMode = D3D11_CULL_NONE;
	// 面の表裏を定義(true = 反時計回りの時表面になる)
	rdc.FrontCounterClockwise = true;
	Device::GetInstance()->GetPtrDevice()
		->CreateRasterizerState(&rdc, &mp_ras_state);
}