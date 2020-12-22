#include"BufferTemplate.h"




BufferTemplate::BufferTemplate() {

	mp_buffer = nullptr;
}


BufferTemplate::~BufferTemplate() {
	Release();
}


bool BufferTemplate::Init(
	ID3D11Device*dev,
	UINT byte_width,
	void*list,
	D3D11_BIND_FLAG bind_state
) {


	if (mp_buffer) {
		return false;
	}

	D3D11_BUFFER_DESC desc;

	// 頂点バッファの初期化設定
	desc.ByteWidth = byte_width;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bind_state;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;

	// 初期化時に設定するバッファデータ
	data.pSysMem = list;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, &data, &mp_buffer)))
	{
		return false;
	}

	return true;
}


bool BufferTemplate::Init(
	ID3D11Device* dev,
	UINT const_struct_size,
	D3D11_BIND_FLAG bind
) {

	if (mp_buffer) {
		return false;
	}

	D3D11_BUFFER_DESC desc;

	// 頂点バッファの初期化設定
	desc.ByteWidth = const_struct_size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bind;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	
	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, NULL, &mp_buffer)))
	{
		return false;
	}

	return true;
}


bool BufferTemplate::Init(
	ID3D11Device* dev,
	const D3D11_BUFFER_DESC& desc,
	void* custom_vertex_list
) {


	if (mp_buffer) {
		return false;
	}

	D3D11_SUBRESOURCE_DATA data;
	// 初期化時に設定するバッファデータ
	data.pSysMem = custom_vertex_list;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, &data, &mp_buffer)))
	{
		return false;
	}
	return true;
}


bool BufferTemplate::Init(
	ID3D11Device* dev,
	const D3D11_BUFFER_DESC& desc,
	const D3D11_SUBRESOURCE_DATA& res_data
) {

	if (mp_buffer) {
		return false;
	}

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, &res_data,&mp_buffer)))
	{
		return false;
	}

	return true;
}


void BufferTemplate::Release() {

	if (mp_buffer != nullptr) {
		mp_buffer->Release();
		mp_buffer = nullptr;
	}
}


ID3D11Buffer* BufferTemplate::GetBuffer() {
	return  mp_buffer;
}