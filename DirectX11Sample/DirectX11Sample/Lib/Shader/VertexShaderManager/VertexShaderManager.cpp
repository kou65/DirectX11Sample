#include"VertexShaderManager.h"
#include"../../Device/Device.h"
#include"../Factory/VertexShaderFactory/VertexShaderFactory.h"



VertexShaderManager::VertexShaderManager() {

	// 生成者を作成する
	mp_vs_factory_list.emplace_back(new VertexShaderFactory);
}


VertexShaderManager::~VertexShaderManager() {

	// for文
	for (auto & i : mp_vs_factory_list) {
		i.reset();
	}

	mp_vs_factory_list.clear();
}


bool VertexShaderManager::Create(
	const std::string&cso_file_path,
	ConstantShader::VSType register_type
) {

	// すでに登録されているなら生成しない
	if (mp_vs_list.count(register_type) != 0) {
		return false;
	}

	VertexShader* p_vs = nullptr;

	for (auto & i : mp_vs_factory_list) {
		p_vs = i->Create(register_type);

		// 生成物が見つかったら
		if (p_vs != nullptr) {
			break;
		}
	}

	// 生成物が見つかっていない
	if (p_vs == nullptr) {
		return false;
	}

	// 生成
	mp_vs_list[register_type] = p_vs;

	// バーテックスシェーダー作成
	if (mp_vs_list[register_type]->Create(
		Device::GetInstance()->GetPtrDevice(),
		cso_file_path
	) == false) {
		return false;
	}

	return true;
}


void VertexShaderManager::Destroy(
	ConstantShader::VSType register_type
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
	ConstantShader::VSType type
) {

	if (mp_vs_list.count(type) == 0) {
		return nullptr;
	}

	return mp_vs_list[type];
}
