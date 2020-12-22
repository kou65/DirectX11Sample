#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_



#include"../../Device/Device.h"



/**
* @brief 定数シェーダーバッファ
*/
class ConstBuffer {
public:


	/**
	* @brief コンストラクタ
	*/
	ConstBuffer();


	/**
	* @brief デストラクタ
	*/
	~ConstBuffer();


	// コピーコンストラクタ（暗黙的コピー）
	ConstBuffer(const ConstBuffer&src) {
		src.mp_buffer->AddRef();
		mp_buffer = src.mp_buffer;
		m_slot_number = src.m_slot_number;
	}

	// =演算子のオーバーロード（明示的コピー）
	void operator =(const ConstBuffer&src) {
		if (src.mp_buffer) {
			src.mp_buffer->AddRef();
		}
		if (mp_buffer) {
			mp_buffer->Release();
		}

		mp_buffer = src.mp_buffer;
		m_slot_number = src.m_slot_number;
	}

	/**
	* @brief バッファの作成
	*/
	bool Create(
		ID3D11Device* dev,
		UINT const_struct_size,
		int slot_number
	);


	/**
	* @brief スロット番号を返す
	*/
	int GetSlotNum();


	/**
	* @brief バッファを返す
	*/
	ID3D11Buffer* GetBuffer();


private:


	//! バッファ
	ID3D11Buffer*mp_buffer;

	//! 登録スロット番号
	int m_slot_number;


};

#endif