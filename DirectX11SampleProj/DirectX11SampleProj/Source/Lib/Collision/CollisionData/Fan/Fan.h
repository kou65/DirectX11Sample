#ifndef FAN_H
#define FAN_H

#include"../../../../Vec3/Vec3.h"


/**
* @brief 扇型
*/
struct Fan {

	Fan() {
		rad = 0.f;
		range_len = 0.f;
	}

	// 中心点座標
	Vec3 center_pos;

	// 扇の範囲(角度)
	float rad;

	// 扇の範囲(長さ)
	float range_len;

	// 扇の回転角度
	Vec3 rota;

	// 位置
	Vec3 pos;
};

#endif


