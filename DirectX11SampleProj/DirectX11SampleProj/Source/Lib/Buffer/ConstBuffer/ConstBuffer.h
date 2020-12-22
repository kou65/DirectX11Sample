#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_



#include"../../Device/Device.h"



/**
* @brief �萔�V�F�[�_�[�o�b�t�@
*/
class ConstBuffer {
public:


	/**
	* @brief �R���X�g���N�^
	*/
	ConstBuffer();


	/**
	* @brief �f�X�g���N�^
	*/
	~ConstBuffer();


	// �R�s�[�R���X�g���N�^�i�ÖٓI�R�s�[�j
	ConstBuffer(const ConstBuffer&src) {
		src.mp_buffer->AddRef();
		mp_buffer = src.mp_buffer;
		m_slot_number = src.m_slot_number;
	}

	// =���Z�q�̃I�[�o�[���[�h�i�����I�R�s�[�j
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
	* @brief �o�b�t�@�̍쐬
	*/
	bool Create(
		ID3D11Device* dev,
		UINT const_struct_size,
		int slot_number
	);


	/**
	* @brief �X���b�g�ԍ���Ԃ�
	*/
	int GetSlotNum();


	/**
	* @brief �o�b�t�@��Ԃ�
	*/
	ID3D11Buffer* GetBuffer();


private:


	//! �o�b�t�@
	ID3D11Buffer*mp_buffer;

	//! �o�^�X���b�g�ԍ�
	int m_slot_number;


};

#endif