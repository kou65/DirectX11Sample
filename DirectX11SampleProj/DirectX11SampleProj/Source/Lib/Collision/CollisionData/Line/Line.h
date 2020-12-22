#ifndef LINE_H
#define LINE_H

#include"../../CollisionData/Point/Point.h"


/**
* @brief 直線
*/
struct Line {


	/**
	* @brief コンストラクタ
	*/
	Line() {};


	/**
	* @brief 点座標を返す
	*/
	Vec3 GetPoint(float t)const;

	//! 点
	Point p;

	//! 方向
	Vec3 v;

};

#endif
