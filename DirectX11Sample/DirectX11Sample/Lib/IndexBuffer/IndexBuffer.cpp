#include"IndexBuffer.h"



IndexBuffer::IndexBuffer() {

	mp_buffer = nullptr;
}


IndexBuffer::~IndexBuffer() {

}


bool IndexBuffer::Init(
	ID3D11Device* dev,
	UINT size,
	void* custom_vertex_list
) {

	D3D11_BUFFER_DESC desc;
	// 頂点バッファの初期化設定
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

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


bool IndexBuffer::Init(
	ID3D11Device* dev,
	const D3D11_BUFFER_DESC& desc,
	void* custom_vertex_list
) {

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


bool IndexBuffer::Init(
	ID3D11Device* dev,
	const D3D11_BUFFER_DESC& desc,
	const D3D11_SUBRESOURCE_DATA& res_data
) {

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, &res_data, &mp_buffer)))
	{
		return false;
	}
	return true;
}


void IndexBuffer::Release() {

	if (mp_buffer != nullptr) {
		mp_buffer->Release();
	}
}


ID3D11Buffer *IndexBuffer::GetBuffer() {
	return mp_buffer;
}