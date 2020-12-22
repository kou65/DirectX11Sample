#ifndef MOUSE_H_
#define MOUSE_H_

#include<Windows.h>


/* ���͂�Input�ɂ���Key�N���X�ōs���Ă������� */

/**
* @class Mouse 
* @brief �V���O���g���̃}�E�X����N���X
*/
class Mouse {
public:

	/**
	* @brief �C���^�[�t�F�C�X�擾
	*/
	static  Mouse* GetInterface() {
		static Mouse m;
		return &m;
	}


	/**
	* @brief �}�E�X�̈ʒu���Z�b�g
	*/
	void SetPos(
		const int& x,
		const int& y
	);


	/**
	* @brief �}�E�X�̌��݈ʒu���擾
	*/
	void GetPos(
		float& x,
		float& y
	);


	/**
	* @brief �}�E�X�J�[�\��������
	*/
	bool IsShow(bool is_show);

};

#endif

