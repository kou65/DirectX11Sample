#ifndef MSG_H_
#define MSG_H_

#include<Windows.h>
#include<string>


/**
* @brief namespace Windows�̃V�X�e���֐��Q
*/
namespace WindowsSystem {


	/**
	* @brief ���b�Z�[�W�̑���M���s��
	* @return bool ���b�Z�[�W���M�I�� = true ����ȊO = false
	*/
	bool ProcessMessage();


	/**
	* @brief ���b�Z�[�W�{�b�N�X���o��������
	*/
	void TextMessageBox(const std::string& string);

}

#endif