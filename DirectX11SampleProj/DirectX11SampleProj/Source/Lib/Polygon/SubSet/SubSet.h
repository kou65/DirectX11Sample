#ifndef SUB_SET_H_
#define SUB_SET_H_



#include<d3d11.h>



/**
* @brief ���b�V���̕`�����؂�T�u�Z�b�g
*/
struct SubSet {


	/**
	* @brief �R���X�g���N�^
	*/
	SubSet() {
		count = 0;
		start = 0;
	}


	// �|���S���̐�
	UINT count;

	// �|���S���𐔂���X�^�[�g�n�_
	UINT start;


};

#endif
