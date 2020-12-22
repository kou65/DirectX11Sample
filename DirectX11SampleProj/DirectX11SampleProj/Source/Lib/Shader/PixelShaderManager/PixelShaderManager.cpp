#include"PixelShaderManager.h"
#include"../../Device/Device.h"
#include"../Factory/PixelShaderFactory/PixelShaderFactory.h"



PixelShaderManager::PixelShaderManager() {

	mp_ps_factory_list.emplace_back(new PixelShaderFactory);
}


PixelShaderManager::~PixelShaderManager() {


	// for文
	for (auto& i : mp_ps_factory_list) {
		i.reset();
	}

	mp_ps_factory_list.clear();
}


bool PixelShaderManager::Create(
	const std::string&cso_file_path,
	ConstShader::PSType register_type
) {

	// すでに登録されているなら生成しない
	if (mp_ps_list.count(register_type) != 0) {
		return false;
	}

	PixelShader * p_ps = nullptr;

	// ファクトリー配列
	for (auto& i : mp_ps_factory_list){
		p_ps = i->Create(register_type);

		// 生成物が見つかったら
		if (p_ps != nullptr) {
			break;
		}
	}

	// 生成物が見つかっていない
	if (p_ps == nullptr) {
		p_ps = new PixelShader();
	}

	// 生成
	mp_ps_list[register_type] = p_ps;

	// バーテックスシェーダー作成
	if (mp_ps_list[register_type]->Create(
		Device::GetInstance()->GetPtrDevice(),
		cso_file_path
	) == false) {
		return false;
	}

	return true;
}


void PixelShaderManager::Destroy(
	ConstShader::PSType register_type
) {

	// 探す
	decltype(mp_ps_list)::iterator it =
		mp_ps_list.find(register_type);

	// メモリ削除
	delete mp_ps_list[register_type];

	// endが帰ってきていないなら見つかった
	if (it != mp_ps_list.end()) {

		// 要素を削除
		mp_ps_list.erase(it);
	}
}


void PixelShaderManager::DestroyEverything() {

	// メモリを全て削除
	for (auto itr = mp_ps_list.begin(); itr != mp_ps_list.end(); itr++) {

		delete itr->second;
	}

	// 全ての要素を解放
	mp_ps_list.clear();
}


PixelShader* PixelShaderManager::GetPtr(
	ConstShader::PSType type
) {

	if (mp_ps_list.count(type) == 0) {
		return nullptr;
	}

	return mp_ps_list[type];
}
