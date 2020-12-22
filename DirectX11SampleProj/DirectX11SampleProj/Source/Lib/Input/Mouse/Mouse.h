#ifndef MOUSE_H_
#define MOUSE_H_

#include<Windows.h>


/* 入力はInputにあるKeyクラスで行ってください */

/**
* @class Mouse 
* @brief シングルトンのマウス操作クラス
*/
class Mouse {
public:

	/**
	* @brief インターフェイス取得
	*/
	static  Mouse* GetInterface() {
		static Mouse m;
		return &m;
	}


	/**
	* @brief マウスの位置をセット
	*/
	void SetPos(
		const int& x,
		const int& y
	);


	/**
	* @brief マウスの現在位置を取得
	*/
	void GetPos(
		float& x,
		float& y
	);


	/**
	* @brief マウスカーソルを消す
	*/
	bool IsShow(bool is_show);

};

#endif

