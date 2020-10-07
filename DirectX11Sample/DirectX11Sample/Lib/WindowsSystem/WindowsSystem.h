#ifndef MSG_H_
#define MSG_H_

#include<Windows.h>
#include<string>


/**
* @brief namespace Windowsのシステム関数群
*/
namespace WindowsSystem {


	/**
	* @brief メッセージの送受信を行う
	* @return bool メッセージ送信終了 = true それ以外 = false
	*/
	bool ProcessMessage();


	/**
	* @brief メッセージボックスを出現させる
	*/
	void TextMessageBox(const std::string& string);

}

#endif