#include"Buffer.h"




Buffer::Buffer() {

	mp_buffer = nullptr;
}


Buffer::~Buffer() {
	Release();
}


bool Buffer::Init(
	ID3D11Device* dev,
	UINT size,
	void* list,
	D3D11_BIND_FLAG bind
) {

	Release();

	D3D11_BUFFER_DESC desc;
	// 頂点バッファの初期化設定
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = bind;
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


bool Buffer::Init(
	ID3D11Device* dev,
	UINT const_struct_size,
	D3D11_BIND_FLAG bind
) {

	Release();

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


bool Buffer::Init(
	ID3D11Device* dev,
	const D3D11_BUFFER_DESC& desc,
	void* custom_vertex_list
) {

	Release();

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


bool Buffer::Init(
	ID3D11Device* dev,
	const D3D11_BUFFER_DESC& desc,
	const D3D11_SUBRESOURCE_DATA& res_data
) {

	Release();

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, &res_data, &mp_buffer)))
	{
		return false;
	}
	return true;
}


void Buffer::Release() {

	// ポインタが存在するなら解放
	if (mp_buffer != nullptr) {
		mp_buffer->Release();
		mp_buffer = nullptr;
	}
}


ID3D11Buffer* Buffer::GetBuffer() {
	return mp_buffer;
}