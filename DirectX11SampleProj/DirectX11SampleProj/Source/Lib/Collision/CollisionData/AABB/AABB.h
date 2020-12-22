#ifndef AABB_H
#define AABB_H
#include"../../../../Vec3/Vec3.h"


/**
* @brief 軸平行境界ボックス(AABB)
*/
struct AABB {

	//! 最大
	Vec3 max;

	//! 最小
	Vec3 min;
};

#endif
