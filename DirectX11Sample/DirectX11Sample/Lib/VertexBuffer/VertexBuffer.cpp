#include"VertexBuffer.h"



VertexBuffer::VertexBuffer() {

	mp_vertex_buffer = nullptr;
}


VertexBuffer::~VertexBuffer() {

}


bool VertexBuffer::Init(
ID3D11Device*dev,
UINT size,
void * custom_vertex_list
) {

	D3D11_BUFFER_DESC desc;

	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	// 初期化時に設定するバッファデータ
	data.pSysMem = custom_vertex_list;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, &data, &mp_vertex_buffer)))
	{
		return false;
	}
	return true;
}


bool VertexBuffer::Init(
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
	if (FAILED(dev->CreateBuffer(&desc, &data, &mp_vertex_buffer)))
	{
		return false;
	}
	return true;
}


bool VertexBuffer::Init(
	ID3D11Device* dev,
	const D3D11_BUFFER_DESC& desc,
	const D3D11_SUBRESOURCE_DATA&res_data
) {

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, &res_data, &mp_vertex_buffer)))
	{
		return false;
	}
	return true;
}


void VertexBuffer::Release() {

	if (mp_vertex_buffer != nullptr) {
		mp_vertex_buffer->Release();
	}
}


ID3D11Buffer *VertexBuffer::GetBuffer() {
	return mp_vertex_buffer;
}