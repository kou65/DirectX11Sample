#ifndef SUB_SET_H_
#define SUB_SET_H_



#include<d3d11.h>



/**
* @brief メッシュの描画を区切るサブセット
*/
struct SubSet {


	/**
	* @brief コンストラクタ
	*/
	SubSet() {
		count = 0;
		start = 0;
	}


	// ポリゴンの数
	UINT count;

	// ポリゴンを数えるスタート地点
	UINT start;


};

#endif
