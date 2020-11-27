#include"PrimitiveRenderer.h"
#include"../Device/Device.h"
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"

// 練習用
void SetUpConstBuffer(
	float aspect_width,
	float aspect_height,
	Buffer* p_c_b
);


PrimitiveRenderer::PrimitiveRenderer() {


}


bool PrimitiveRenderer::Create() {

	return true;
}


void PrimitiveRenderer::RenderingPolygonByDeviceView(
	PolygonPrimitive* pol,
	ConstantShader::VSType vs_type,
	ConstantShader::PSType ps_type
) {

	RenderingPolygon(
		Device::GetInstance()->GetPtrImmContext(),
		Device::GetInstance()->GetPtrRenderTargetView(),
		Device::GetInstance()->GetPtrDepthStencilView(),
		pol,
		vs_type,
		ps_type
	);
}


void PrimitiveRenderer::RenderingPolygon(
	ID3D11DeviceContext*p_context,
	ID3D11RenderTargetView*p_render_target,
	ID3D11DepthStencilView*p_depth_stencile,
    PolygonPrimitive* pol,
	ConstantShader::VSType vs_type,
	ConstantShader::PSType ps_type
) {

	// ポリゴンの描画で必要なことは
	// 適切な情報をGPU側に送信すること

	UINT strides = pol->GetCustomVertexSize();

	UINT offsets = 0;

	ID3D11Buffer * buff = 
		pol->GetVertexBuffer()->GetBuffer();


	// 描画で使用する入力レイアウトを設定する
	p_context->IASetInputLayout(
		pol->GetPtrInputLayout()
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
		VertexShaderManager::GetInstance()->
		GetPtr(ConstantShader::VSType::NORMAL)->GetInterfacePtr(),
		NULL,
		0
	);

	// ピクセルシェーダーをセットする
	p_context->PSSetShader(
		PixelShaderManager::GetInstance()->
		GetPtr(ConstantShader::PSType::NORMAL)->GetInterfacePtr(),
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
		// 頂点の数
		pol->GetVertexCount(), 
		// 頂点バッファの描画開始インデックス
		pol->GetStartVertex()  
	);


	ClearRenderingInfo(
		p_context
	);
}


void PrimitiveRenderer::RenderingMesh(
	ID3D11DeviceContext* p_context,
	ID3D11RenderTargetView* p_render_target,
	ID3D11DepthStencilView* p_depth_stencile,
	MeshPrimitive* mesh,
	ConstantShader::VSType vs_type,
	ConstantShader::PSType ps_type
) {


	UINT strides = 
		mesh->GetCustomVertexSize();

	UINT offsets = 0;

	// 描画で使用する入力レイアウトを設定する
	p_context->IASetInputLayout(
		mesh->GetPtrInputLayout()
	);


	// バーテックスシェーダーをセットする
	p_context->VSSetShader(
		VertexShaderManager::GetInstance()->
		GetPtr(vs_type)->GetInterfacePtr(),
		NULL,
		0
	);


	// ピクセルシェーダーをセットする
	p_context->PSSetShader(
		PixelShaderManager::GetInstance()->
		GetPtr(ps_type)->GetInterfacePtr(),
		NULL,
		0
	);

	// 描画処理の出力先ビューの設定
	p_context->OMSetRenderTargets(
		1,
		&p_render_target,
		p_depth_stencile
	);

	// メッシュ
	ID3D11Buffer* p_buf = 
		mesh->GetVertexBuffer()->GetBuffer();

	// バーテックスバッファのセット
	p_context->IASetVertexBuffers(
		0,
		1,
		&p_buf,
		&strides, 
		&offsets
	);

	ID3D11Buffer* p_ibuf = mesh->GetIndexBuffer()->GetBuffer();

	// インデックスバッファのセット
	p_context->
		IASetIndexBuffer(
			p_ibuf,
			DXGI_FORMAT_R16_UINT,
			0
		);

	// 定数バッファ
	ID3D11Buffer* p_vs_const_buffer =
		VertexShaderManager::GetInstance()->
		GetPtr(vs_type)->GetConstBuffer()->GetBuffer();

	// vsコンスタントバッファセット
	p_context->VSSetConstantBuffers(
		0,
		1,
		&p_vs_const_buffer
	);

	ID3D11Buffer* p_ps_const_buffer =
		PixelShaderManager::GetInstance()->
		GetPtr(ps_type)->GetConstBuffer()->GetBuffer();

		// psコンスタントバッファセット
		p_context->PSSetConstantBuffers(
			0,
			1,
			&p_ps_const_buffer
		);


	// 形状描画
	p_context->
		IASetPrimitiveTopology(
			mesh->GetPrimitive()
		);

	// 配列描画
	p_context->DrawIndexed(
		mesh->GetIndexCount(),
		0, 
		0
	);


	// レンダリング情報をクリアする
	ClearRenderingInfo(
		p_context
	);

}


void PrimitiveRenderer::RenderingMeshByDeviceView(
	MeshPrimitive* mesh,
	ConstantShader::VSType vs_type,
	ConstantShader::PSType ps_type
) {

	// メッシュの描画
	RenderingMesh(
		Device::GetInstance()->GetPtrImmContext(),
		Device::GetInstance()->GetPtrRenderTargetView(),
		Device::GetInstance()->GetPtrDepthStencilView(),
		mesh,
		vs_type,
		ps_type
	);
}



void PrimitiveRenderer::ClearRenderingInfo(
	ID3D11DeviceContext* p_context
) {

	// nullを入れておく
	//p_context->VSSetConstantBuffers(
	//	0,
	//	1,
	//	NULL
	//);
	//
	//p_context->PSSetConstantBuffers(
	//	0,
	//	1,
	//	NULL
	//);
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
