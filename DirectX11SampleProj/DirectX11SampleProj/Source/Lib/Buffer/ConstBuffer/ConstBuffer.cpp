#include"ConstBuffer.h"



ConstBuffer::ConstBuffer() {

	m_slot_number = 0;
	mp_buffer = nullptr;
}


ConstBuffer::~ConstBuffer() {

	//mp_buffer->Release();

	if (mp_buffer != nullptr) {
		mp_buffer->Release();
		mp_buffer = nullptr;
	}

}


bool ConstBuffer::Create(
	ID3D11Device* dev,
	UINT const_struct_size,
	int slot_number
) {

	if (mp_buffer) {
		return false;
	}

	D3D11_BUFFER_DESC desc;

	// 頂点バッファの初期化設定
	desc.ByteWidth = const_struct_size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	// 頂点バッファの生成
	if (FAILED(dev->CreateBuffer(&desc, NULL, &mp_buffer)))
	{
		return false;
	}

	m_slot_number = slot_number;

	return true;
}


int ConstBuffer::GetSlotNum() {
	return m_slot_number;
}


ID3D11Buffer* ConstBuffer::GetBuffer() {
	return mp_buffer;
}