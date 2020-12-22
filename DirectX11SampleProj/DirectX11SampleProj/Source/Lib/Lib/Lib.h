#ifndef LIB_H_
#define LIB_H

#include"../Window/Window.h"
#include"../Device/Device.h"
#include<memory>

/**
* @brief Lib ライブラリの関数をまとめて処理するクラス
*/
class Lib {
public:

	Lib();
	~Lib() {};

	/**
	* @brief ライブラリの初期化
	*/
	bool Init();


	/**
	* @brief 更新
	* @return bool 更新成功 = true 
	*/
	bool Update();


	/**
	* @brief 解放
	*/
	void Release();

private:

	std::unique_ptr<Window>mp_window;
};

#endif
