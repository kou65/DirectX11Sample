#ifndef BUFFER_H_
#define BUFFER_H_



#include"../../Device/Device.h"



/*
* @brief DirectX11�̒��_��C���f�b�N�X�Ȃǂ̃o�b�t�@
*/
class BufferTemplate {
public:


	/**
	* @brief �R���X�g���N�^
	*/
	BufferTemplate();


	/**
	* @brief �f�X�g���N�^
	*/
	~BufferTemplate();


	// �R�s�[�R���X�g���N�^�i�ÖٓI�R�s�[�j
	BufferTemplate(const BufferTemplate& src) {
		src.mp_buffer->AddRef();
		mp_buffer = src.mp_buffer;
	}
	
	// =���Z�q�̃I�[�o�[���[�h�i�����I�R�s�[�j
	void operator =(const BufferTemplate& src) {
		if (src.mp_buffer)
			src.mp_buffer->AddRef();
		if (mp_buffer)
			mp_buffer->Release();
		mp_buffer = src.mp_buffer;
	}


	/**
	* @brief ������
	*/
	bool Init(
		ID3D11Device* dev,
		UINT size,
		void* custom_vertex_list,
		D3D11_BIND_FLAG bind
	);


	/**
	* @brief Desc��null�̏ꍇ�̏�����
	*/
	bool Init(
		ID3D11Device* dev,
		UINT const_struct_size,
		D3D11_BIND_FLAG bind
	);


	/**
	* @brief ������
	*/
	bool Init(
		ID3D11Device* dev,
		const D3D11_BUFFER_DESC& desc,
		const D3D11_SUBRESOURCE_DATA& res_data
	);


	/**
	* @brief ������
	*/
	bool Init(
		ID3D11Device*dev,
		const D3D11_BUFFER_DESC&desc,
		void* custom_vertex_list
	);


	/**
	* @brief ���
	*/
	void Release();


	/**
	* @brief �o�b�t�@��Ԃ�
	*/
	ID3D11Buffer*GetBuffer();


private:


	//! �o�b�t�@
	ID3D11Buffer*mp_buffer;

};


#endif