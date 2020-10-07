#ifndef WINDOW_H_
#define WINDOW_H_

#include<Windows.h>
#include<string>

/*�������邱��

Window�̍쐬

*/

//! unsigned int ��uint�Ƃ��Ē�`
typedef unsigned int uint;

/**
* @class Window
* @brief �E�B���h�E�쐬�N���X
*/
class Window{
public:

	
	/**
	* @brief �R���X�g���N�^
	* @param[in] title �^�C�g����
	* @param[in] width �N���C�A���g�̈扡�̃T�C�Y
	* @param[in] height �N���C�A���g�̈�c�̃T�C�Y
	*/
	Window(
		const std::string&class_name,
		const std::string&title_name,
		const uint& width_size = 1920,
		const uint& height_size = 1080
	);


	/**
	* @brief �E�B���h�E�v���V�[�W��
	* @param[in] window_handle �C�x���g�����������E�B���h�E�̃n���h��
	* @param[in] message_id �C�x���g���b�Z�[�W
	* @param[in] wparam �C�x���g���
	* @param[in] lparam �C�x���g���
	* @return ���b�Z�[�W��������
	*/
	static LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam);


	/**
	* @brief �E�B���h�E�����֐�@n
	* �E�B���h�E�𐶐����Đ���������true�A���s������false��Ԃ�
	* @return �����̐��� ����(true)
	*/
	bool Create();


	/**
	* @brief window�̃N���X�l�[����Ԃ�
	* @return std::string �N���X�l�[��
	*/
	std::string GetWindowName();

private:

	/**
	* @brief �E�B���h�E�N���X�o�^�֐�@n
	* �E�B�h�E���쐬���邽�߂̃E�B���h�E�N���X����o�^���Đ���������true�A���s������false��Ԃ�
	* @return �o�^�̐��� ����(true)
	*/
	bool EntryWindowClass();

	/**
	* @brief �E�B�h�E�̃��T�C�Y�֐�@n
	* ������ɃN���C�A���g�̈�̃T�C�Y�Ƀ��T�C�Y����
	* @param[in] ���T�C�Y�ΏۂƂȂ�E�B���h�E�n���h��
	*/
	void ResizeWindow(HWND window_handle);

private:

	//! �E�B���h�E�N���X��
	std::string m_class_name;

	//! �^�C�g����
	std::string m_title_name;

	//! ����
	uint m_width_size;

	//! �c��
	uint m_height_size;
};


#endif

/*
�E�B���h�E�����ō������火
http
://www-higashi.ist.osaka-u.ac.jp/~k-maeda/vcpp/sec1-3wnddetail.html
*/