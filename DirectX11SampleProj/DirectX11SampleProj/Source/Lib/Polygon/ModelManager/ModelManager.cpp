#include"ModelManager.h"
#include"../../Shader/ConstShader/ConstShader.h"
#include"../../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../../Shader/PixelShaderManager/PixelShaderManager.h"
#include"../../OBJ/OBJFile/OBJFile.h"



void ModelManager::ChangeVSShader(
	const ConstShader::VSType& vs_type,
	const std::string&register_name
) {

	mp_model_list[register_name]->SetVSType(vs_type);
}


void ModelManager::ChangePSShader(
	const ConstShader::PSType& ps_type,
	const std::string& register_name
) {

	mp_model_list[register_name]->SetPSType(ps_type);
}


void ModelManager::AllChangeVSShader(
	const ConstShader::VSType& vs_type
) {
	for (auto& model : mp_model_list) {
		model.second->SetVSType(vs_type);
	}
}


void ModelManager::AllChangePSShader(
	const ConstShader::PSType& ps_type
) {
	for (auto& model : mp_model_list) {
		model.second->SetPSType(ps_type);
	}
}


bool ModelManager::Load(
	FileFormat format,
	const std::string model_file_path,
	const std::string register_name
) {

	Model model;

	// モデル読み込み
	switch (format)
	{
	case ModelManager::FileFormat::OBJ:

		if (OBJFile::GetInstance()->LoadModel(
			model_file_path,
			register_name,
			model
		) == false) {
			return false;
		}
		break;

	default:
		break;
	}

	return true;
}


void ModelManager::Draw(
	const TS3DMatrixData&ts_mat_data
) {

	int mesh_number = 0;

	// 全てのモデルを描画
	for (auto& model : mp_model_list) {

		DrawSubSet(
			model.second,
			mesh_number
		);
	}
}


void ModelManager::DrawSubSet(
	Model*model,
	const int&mesh_number
) {

	// メッシュ取得
	MeshPrimitive mesh = 
		model->GetMesh(mesh_number);

	// サブセット分回す
	for (int i = 0; mesh.sub_set_list.size(); i++) {

		// 描画
		DrawIndexSubSet(
			model,
			mesh_number,
			i
		);
	}
}


void ModelManager::DrawIndexSubSet(
	Model* model,
	const int& mesh_number,
	const int& sub_set_number
) {

	int mater_index = 0;

	// メッシュの取得
	MeshPrimitive mesh =
		model->GetMesh(mesh_number);

	// マテリアルデータ取得
	MaterialData material_data =
		mesh.material_data_list[mater_index];

	// ここでパラメータで更新セット

	// メッシュ描画
	DrawMesh(
		Device::GetInstance()->GetPtrImmContext(),
		&mesh,
		model->GetVSType(),
		model->GetPSType(),
		mesh.sub_set_list[sub_set_number].start,
		mesh.sub_set_list[sub_set_number].count
	);

}


void ModelManager::DrawMesh(
	ID3D11DeviceContext * p_context,
	MeshPrimitive * mesh,
	ConstShader::VSType vs_type,
	ConstShader::PSType ps_type,
	const int&index_start,
	const int&index_count,
	const int&vs_c_num,
	const int&ps_c_num
) {


	UINT strides = mesh->polygon_primitive.vertex_data_size;

	UINT offsets = 0;

	// 描画で使用する入力レイアウトを設定する
	p_context->IASetInputLayout(
		VertexShaderManager::GetInstance()->
		GetPtr(vs_type)->GetInputLayoutPtr()
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
	//
	//// 描画処理の出力先ビューの設定
	//p_context->OMSetRenderTargets(
	//	1,
	//	&p_render_target,
	//	p_depth_stencile
	//);

	// メッシュ
	ID3D11Buffer* p_vertex_buffer = mesh->polygon_primitive.vertex_buffer.GetBuffer();

	// バーテックスバッファのセット
	p_context->IASetVertexBuffers(
		0,
		1,
		&p_vertex_buffer,
		&strides,
		&offsets
	);

	ID3D11Buffer* p_index_buffer = mesh->index_buffer.GetBuffer();

	// インデックスバッファのセット
	p_context->
		IASetIndexBuffer(
			p_index_buffer,
			mesh->format,
			0
		);

	// 定数バッファ
	ID3D11Buffer* p_vs_const_buffer =
		VertexShaderManager::GetInstance()->
		GetPtr(vs_type)->GetConstBuffer(vs_c_num);

	// vsコンスタントバッファセット
	p_context->VSSetConstantBuffers(
		0,
		1,
		&p_vs_const_buffer
	);

	// ピクセルシェーダー
	ID3D11Buffer* p_ps_const_buffer =
		PixelShaderManager::GetInstance()->
		GetPtr(ps_type)->GetConstBuffer(ps_c_num);


	// psコンスタントバッファセット
	p_context->PSSetConstantBuffers(
		0,
		1,
		&p_ps_const_buffer
	);


	// 形状描画
	p_context->IASetPrimitiveTopology(
			mesh->polygon_primitive.tepology
		);

	// 配列描画
	p_context->DrawIndexed(
		index_count,
		index_start,
		0
	);

}
