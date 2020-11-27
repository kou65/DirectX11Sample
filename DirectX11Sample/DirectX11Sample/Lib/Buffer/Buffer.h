#ifndef BUFFER_H_
#define BUFFER_H_



#include"../Device/Device.h"



/*
* @brief バッファクラス
*/
class Buffer {
public:

	Buffer();
	~Buffer();


	bool Init(
		ID3D11Device* dev,
		UINT size,
		void* custom_vertex_list,
		D3D11_BIND_FLAG bind
	);


	/**
	* @brief Descがnullの場合
	*/
	bool Init(
		ID3D11Device* dev,
		UINT const_struct_size,
		D3D11_BIND_FLAG bind
	);


	bool Init(
		ID3D11Device* dev,
		const D3D11_BUFFER_DESC& desc,
		const D3D11_SUBRESOURCE_DATA& res_data
	);


	bool Init(
		ID3D11Device* dev,
		const D3D11_BUFFER_DESC& desc,
		void* custom_vertex_list
	);


	void Release();
	ID3D11Buffer* GetBuffer();

private:

	ID3D11Buffer* mp_buffer;
};


#endif