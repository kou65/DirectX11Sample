#ifndef VS2D_DATA_H_
#define VS2D_DATA_H_




#include<DirectXMath.h>


using namespace DirectX;


/**
* @brief 2D描画に必要なパラメータ
*/
struct VS2DData {

	XMFLOAT4X4 world;
	XMFLOAT4X4 proj;

};

#endif