#include"VertexShaderManager.h"
#include"../../Device/Device.h"
#include"../Factory/VertexShaderFactory/VertexShaderFactory.h"
#include"../../Device/Device.h"
#include"../../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../../ConstBufferData/LightConstBuffer/LightConstBuffer.h"



VertexShaderManager::VertexShaderManager() {

	// 生成者を作成する
	mp_vs_factory_list.emplace_back(new VertexShaderFactory);

	// デスクをリストにセット
	SetUpInputDescList();
}


VertexShaderManager::~VertexShaderManager() {

	// for文
	for (auto & i : mp_vs_factory_list) {
		i.reset();
	}

	mp_vs_factory_list.clear();
}


bool VertexShaderManager::Create(
	const std::string&cso_file_name,
	const ConstShader::VSType&register_type,
	const ConstShader::InputLayout::InputType input_layout_type
) {

	// すでに登録されているなら生成しない
	if (mp_vs_list.count(register_type) != 0) {
		return false;
	}

	VertexShader*p_vs = nullptr;

	for (auto&i : mp_vs_factory_list) {
		p_vs = i->Create(register_type);

		// 生成物が見つかったら
		if (p_vs != nullptr) {
			break;
		}
	}

	// 生成物が見つかっていない
	if (p_vs == nullptr) {

		// 既存の頂点シェーダーを生成する
		p_vs = new VertexShader();
	}

	// 生成
	mp_vs_list[register_type] = p_vs;

	// バーテックスシェーダー作成
	if (mp_vs_list[register_type]->Create(
		Device::GetInstance()->GetPtrDevice(),
		cso_file_name
	) == false) {
		return false;
	}

	// インプットレイアウト作成
	if (mp_vs_list[register_type]->CreateInputLayout(
		mp_input_desc_list[input_layout_type]
	) == false) {
		return false;
	}

	return true;
}


void VertexShaderManager::Destroy(
	const ConstShader::VSType&register_type
) {

	// 探す
	decltype(mp_vs_list)::iterator it =
		mp_vs_list.find(register_type);

	// メモリ削除
	delete mp_vs_list[register_type];

	// endが帰ってきていないなら見つかった
	if (it != mp_vs_list.end()) {

		// 要素を削除
		mp_vs_list.erase(it);
	}
}


void VertexShaderManager::DestroyEverything() {

	// メモリを全て削除
	for (auto itr = mp_vs_list.begin(); itr != mp_vs_list.end(); itr++) {

		delete itr->second;
	}

	// 全ての要素を解放
	mp_vs_list.clear();
}


VertexShader *VertexShaderManager::GetPtr(
	const ConstShader::VSType&type
) {

	if (mp_vs_list.count(type) == 0) {
		return nullptr;
	}

	return mp_vs_list[type];
}


void VertexShaderManager::SetUpInputDescList() {


	InputDescInfo info;

	// 各インプットレイアウトの情報をセット
	info.p_desc = ConstShader::InputLayout::VER_NOR_DESC;
	info.array_size = ConstShader::InputLayout::VER_NOR_DESC_ARRAY_SIZE;


	mp_input_desc_list[ConstShader::InputLayout::InputType::VER_NOR] = info;
	

	info.p_desc = ConstShader::InputLayout::VER_COL_DESC;
	info.array_size = ConstShader::InputLayout::VER_COL_DESC_ARRAY_SIZE;


	mp_input_desc_list[ConstShader::InputLayout::InputType::VER_COL] = info;


	info.p_desc = ConstShader::InputLayout::VER_NOR_COL_DESC;
	info.array_size = ConstShader::InputLayout::VER_NOR_COL_DESC_ARRAY_SIZE;


	mp_input_desc_list[ConstShader::InputLayout::InputType::VER_NOR_COL] = 
		info;

}