#include"PrimitiveRenderer.h"
#include"../Device/Device.h"
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"



PrimitiveRenderer::PrimitiveRenderer() {

	mp_ras_state = nullptr;
}


bool PrimitiveRenderer::Create() {

	return true;
}


void PrimitiveRenderer::RenderingPolygonByDeviceView(
	PolygonPrimitive* pol,
	ConstShader::VSType vs_type,
	ConstShader::PSType ps_type
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
	ConstShader::VSType vs_type,
	ConstShader::PSType ps_type
) {

	// ポリゴンの描画で必要なことは
	// 適切な情報をGPU側に送信すること

	for (UINT i = 0; i < pol->sub_set_list.size(); ++i) {

		UINT strides = pol->vertex_data_size;

		UINT offsets = 0;

		ID3D11Buffer* buff =
			pol->vertex_buffer.GetBuffer();


		// 描画で使用する入力レイアウトを設定する
		p_context->IASetInputLayout(
			VertexShaderManager::GetInstance()->
			GetPtr(vs_type)->GetInputLayoutPtr()
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
			pol->tepology
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

		// 頂点描画
		p_context->Draw(
			// 頂点の数
			pol->sub_set_list[i].count,
			// 頂点バッファの描画開始インデックス
			pol->sub_set_list[i].start
		);


		ClearRenderingInfo(
			p_context
		);
	}
}


void PrimitiveRenderer::RenderingMesh(
	ID3D11DeviceContext* p_context,
	ID3D11RenderTargetView* p_render_target,
	ID3D11DepthStencilView* p_depth_stencile,
	MeshPrimitive* mesh,
	ConstShader::VSType vs_type,
	ConstShader::PSType ps_type,
	const int&vs_c_num,
	const int&ps_c_num
) {

	// サブセット分回す
	for (int i = 0; i < mesh->sub_set_list.size(); i++) {

		UINT strides = mesh->polygon_primitive.vertex_data_size;

		UINT offsets = 0;

		// 描画で使用する入力レイアウトを設定する
		p_context->IASetInputLayout(
			VertexShaderManager::GetInstance()->
			GetPtr(ConstShader::VSType::NORMAL)->GetInputLayoutPtr()
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
		ID3D11Buffer* p_v_buf = mesh->polygon_primitive.vertex_buffer.GetBuffer();

		// バーテックスバッファのセット 
		p_context->IASetVertexBuffers(
			0,
			1,
			&p_v_buf,
			&strides,
			&offsets
		);

		ID3D11Buffer* p_i_buf = mesh->index_buffer.GetBuffer();

		// インデックスバッファのセット
		p_context->
			IASetIndexBuffer(
				p_i_buf,
				mesh->format,
				0
			);

		// 定数バッファ
		ID3D11Buffer* p_vs_const_buffer =
			VertexShaderManager::GetInstance()->
			GetPtr(vs_type)->GetConstBuffer(vs_c_num);

		// vsコンスタントバッファセット
		p_context->VSSetConstantBuffers(
			vs_c_num,
			1,
			&p_vs_const_buffer
		);

		ID3D11Buffer* p_ps_const_buffer =
			PixelShaderManager::GetInstance()->
			GetPtr(ps_type)->GetConstBuffer(ps_c_num);

		// psコンスタントバッファセット
		p_context->PSSetConstantBuffers(
			ps_c_num, // バッファスロット番号
			1, // 送り込むバッファの数
			&p_ps_const_buffer
		);


		// 形状描画
		p_context->
			IASetPrimitiveTopology(
				mesh->polygon_primitive.tepology
			);

		// 配列描画
		p_context->DrawIndexed(
			mesh->sub_set_list[i].count,
			mesh->sub_set_list[i].start,
			0
		);


		// レンダリング情報をクリアする
		ClearRenderingInfo(
			p_context
		);

	}

}


void PrimitiveRenderer::RenderingMeshByDeviceView(
	MeshPrimitive* mesh,
	ConstShader::VSType vs_type,
	ConstShader::PSType ps_type,
	const int&vs_c_num,
	const int&ps_c_num
) {

	// 定数バッファのセットはまた別で作る
	// メッシュの描画
	RenderingMesh(
		Device::GetInstance()->GetPtrImmContext(),
		Device::GetInstance()->GetPtrRenderTargetView(),
		Device::GetInstance()->GetPtrDepthStencilView(),
		mesh,
		vs_type,
		ps_type,
		vs_c_num,
		ps_c_num
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


void PrimitiveRenderer::VSSetConstBuffer(
	ConstShader::VSType vs_type,
	int slot_num
) {

	// 定数バッファ
	ID3D11Buffer* p_vs_const_buffer = 
		VertexShaderManager::GetInstance()->
		GetPtr(vs_type)->GetConstBuffer(slot_num);

	// vsコンスタントバッファセット
	Device::GetInstance()->GetPtrImmContext()->VSSetConstantBuffers(
		slot_num,
		1,
		&p_vs_const_buffer
	);


}


void PrimitiveRenderer::PSSetConstBuffer(
	ConstShader::PSType ps_type,
	int slot_num
) {

	ID3D11Buffer* p_ps_const_buffer =
		PixelShaderManager::GetInstance()->
		GetPtr(ps_type)->GetConstBuffer(slot_num);

	// psコンスタントバッファセット
	Device::GetInstance()->GetPtrImmContext()->PSSetConstantBuffers(
		slot_num, // バッファスロット番号
		1, // 送り込むバッファの数
		&p_ps_const_buffer
	);
}
