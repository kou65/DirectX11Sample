#include"VertexShader.h"
#include<d3dcompiler.h>

VertexShader::VertexShader() {

	mp_vs = nullptr;
}


VertexShader::~VertexShader() {

	if (mp_vs != nullptr) {
		mp_vs->Release();
	}
}


bool VertexShader::Create(
	ID3D11Device* p_device,
	const std::string& file_name
) {

	if (p_device == nullptr) {
		return false;
	}

	// シェーダー作成
	if (ShaderBase::Create(p_device, file_name) == false) {
		return false;
	}

	HRESULT hr = NULL;

	// 頂点シェーダー読み込み
	hr =
		p_device->CreateVertexShader(
			mp_data,
			m_size,
			nullptr,
			&mp_vs
		);

	if (hr != S_OK) {
		return false;
	}

	return true;
}


ID3D11VertexShader *VertexShader::GetInterfacePtr() {
	return mp_vs;
}