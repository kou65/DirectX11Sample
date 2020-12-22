#ifndef BUFFER_H_
#define BUFFER_H_



#include"../../Device/Device.h"



/*
* @brief DirectX11の頂点やインデックスなどのバッファ
*/
class BufferTemplate {
public:


	/**
	* @brief コンストラクタ
	*/
	BufferTemplate();


	/**
	* @brief デストラクタ
	*/
	~BufferTemplate();


	// コピーコンストラクタ（暗黙的コピー）
	BufferTemplate(const BufferTemplate& src) {
		src.mp_buffer->AddRef();
		mp_buffer = src.mp_buffer;
	}
	
	// =演算子のオーバーロード（明示的コピー）
	void operator =(const BufferTemplate& src) {
		if (src.mp_buffer)
			src.mp_buffer->AddRef();
		if (mp_buffer)
			mp_buffer->Release();
		mp_buffer = src.mp_buffer;
	}


	/**
	* @brief 初期化
	*/
	bool Init(
		ID3D11Device* dev,
		UINT size,
		void* custom_vertex_list,
		D3D11_BIND_FLAG bind
	);


	/**
	* @brief Descがnullの場合の初期化
	*/
	bool Init(
		ID3D11Device* dev,
		UINT const_struct_size,
		D3D11_BIND_FLAG bind
	);


	/**
	* @brief 初期化
	*/
	bool Init(
		ID3D11Device* dev,
		const D3D11_BUFFER_DESC& desc,
		const D3D11_SUBRESOURCE_DATA& res_data
	);


	/**
	* @brief 初期化
	*/
	bool Init(
		ID3D11Device*dev,
		const D3D11_BUFFER_DESC&desc,
		void* custom_vertex_list
	);


	/**
	* @brief 解放
	*/
	void Release();


	/**
	* @brief バッファを返す
	*/
	ID3D11Buffer*GetBuffer();


private:


	//! バッファ
	ID3D11Buffer*mp_buffer;

};


#endif