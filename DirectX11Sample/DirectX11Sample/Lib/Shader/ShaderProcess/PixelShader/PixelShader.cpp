#include"PixelShader.h"


PixelShader::PixelShader() {

	mp_interface = nullptr;
}


PixelShader::~PixelShader() {

	if (mp_interface != nullptr) {
		mp_interface->Release();
	}
}


bool PixelShader::Create(
	ID3D11Device* p_device,
	const std::string& file_name
) {

	// 作成
	if (ShaderBase::Create(p_device, file_name) == false)
	{
		return false;
	}

	HRESULT hr = NULL;

	// ピクセルシェーダー作成
	hr = p_device->CreatePixelShader(
			mp_data, m_size, nullptr, &mp_interface);

	if (hr != S_OK)
	{
		return false;
	}

	return true;
}


ComPtr<ID3D11PixelShader> PixelShader::GetInterfacePtr() {

	return mp_interface;
}
