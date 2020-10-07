#include"VertexShader.h"


VertexShader::VertexShader() {

	mp_interface = nullptr;
}


VertexShader::~VertexShader() {

	if (mp_interface != nullptr) {
		mp_interface->Release();
	}
}


bool VertexShader::Create(
	ID3D11Device* p_device,
	const std::string& file_name
) {

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
			&mp_interface
		);

	if (hr != S_OK) {
		return false;
	}

	return true;
}


ComPtr<ID3D11VertexShader>VertexShader::GetInterfacePtr() {
	return mp_interface;
}