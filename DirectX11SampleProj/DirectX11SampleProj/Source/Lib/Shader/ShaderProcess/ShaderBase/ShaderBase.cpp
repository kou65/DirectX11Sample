
#include"ShaderBase.h"
#include<d3dcompiler.h>

// シェーダーコンパイル用の静的ライブラリをリンク
#pragma comment(lib,"d3dcompiler.lib")



ShaderBase::ShaderBase() {

	mp_data = nullptr;
	m_size = 0;
}


ShaderBase::~ShaderBase() {

	delete[] mp_data;

	// 定数バッファ削除
	m_const_buffer_list.clear();
};


bool ShaderBase::Create(
	ID3D11Device* p_device,
	const std::string& file_name
) {

	// ファイル読み込み
	m_size = LoadFile(file_name);

	if (m_size == 0) {
		return false;
	}

	return true;
}


int ShaderBase::LoadFile(
	const std::string& file_name
) {

	FILE* fp = nullptr;

	// オープン
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp == nullptr) {
		return 0;
	}

	/* ファイルの終端まで行き、サイズを取得、始めに戻す */

	// ファイル位置表示の値を変更する(ファイルの終わり)
	fseek(fp, 0, SEEK_END);

	// ファイル位置表示子
	m_size = ftell(fp);

	// ファイルの始めに変更
	fseek(fp, 0, SEEK_SET);

	mp_data = new char[m_size];

	// バイト分読み込む
	fread_s(mp_data, m_size, m_size, 1, fp);

	fclose(fp);

	return m_size;
}


ID3D11Buffer *ShaderBase::GetConstBuffer(
	const int&slot_number
) {

	for (auto&c : m_const_buffer_list) {

		// 指定スロット番号があればそれを返す
		if(slot_number == c.GetSlotNum())
		return c.GetBuffer();
	}

	// なかった場合
	return nullptr;
}


bool ShaderBase::CreateConstBuffer(
	const int&slot_number,
	const UINT&buffer_size
) {

	// APIレベルで現在使用可能な定数バッファの数より上ならはじく
	if (slot_number >= D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT) {
		return false;
	}

	for (auto c : m_const_buffer_list) {

		if (slot_number == c.GetSlotNum()) {
			return false;
		}
	}

	ConstBuffer const_buffer;

	if (const_buffer.Create(
		Device::GetInstance()->GetPtrDevice(),
		buffer_size,
		slot_number
	) == false) {
		return false;
	}

	m_const_buffer_list.emplace_back(
		const_buffer
	);

	return true;
}