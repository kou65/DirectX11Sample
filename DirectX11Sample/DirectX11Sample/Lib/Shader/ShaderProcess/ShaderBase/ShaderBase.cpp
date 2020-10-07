
#include"ShaderBase.h"
#include<d3dcompiler.h>

// シェーダーコンパイル用の静的ライブラリをリンク
#pragma comment(lib,"d3dcompiler.lib")



ShaderBase::ShaderBase() {

	mp_data = nullptr;
	m_size = 0;
}


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
