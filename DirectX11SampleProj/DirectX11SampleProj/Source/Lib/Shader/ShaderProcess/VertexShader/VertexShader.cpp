#include"VertexShader.h"
#include<d3dcompiler.h>
#include"../../ConstShader/ConstShader.h"



VertexShader::VertexShader() {

	mp_vs = nullptr;
	mp_input_layout = nullptr;
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
	hr = p_device->CreateVertexShader(
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


bool VertexShader::CreateInputLayout(
	const InputDescInfo&p_input_desc
) {

	//頂点レイアウト作成
	if (FAILED(
		Device::GetInstance()->GetPtrDevice()->CreateInputLayout(
		p_input_desc.p_desc,								// レイアウト設定
		p_input_desc.array_size,									// 配列サイズ
		mp_data,									// レイアウトと関連付ける頂点シェーダのデータ
		m_size,										// レイアウトと関連付ける頂点シェーダのサイズ
		&mp_input_layout)))							// 作成された頂点レイアウトの格納先
	{
		return false;
	}

	return true;
}


ID3D11VertexShader *VertexShader::GetInterfacePtr() {
	return mp_vs;
}


ID3D11InputLayout* VertexShader::GetInputLayoutPtr() {
	return mp_input_layout;
}