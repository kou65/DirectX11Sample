#ifndef LIB_H_
#define LIB_H

#include"../Window/Window.h"
#include"../Device/Device.h"
#include<memory>

/**
* @brief Lib ���C�u�����̊֐����܂Ƃ߂ď�������N���X
*/
class Lib {
public:

	Lib();
	~Lib() {};

	/**
	* @brief ���C�u�����̏�����
	*/
	bool Init();


	/**
	* @brief �X�V
	* @return bool �X�V���� = true 
	*/
	bool Update();


	/**
	* @brief ���
	*/
	void Release();

private:

	std::unique_ptr<Window>mp_window;
};

#endif
