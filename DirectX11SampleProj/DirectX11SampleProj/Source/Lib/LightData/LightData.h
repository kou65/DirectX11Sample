#ifndef LIGHT_DATA_H_
#define LIGHT_DATA_H_


#include<DirectXMath.h>
#include"../MaterialData/MaterialData.h"


using namespace DirectX;


/**
* @brief ライトデータを含む構造体
*/
struct LightData {


	XMFLOAT4 light_pos;     // ライト座標
	XMFLOAT4 light_vector;  // ライト方向
	XMFLOAT4 light_color;   // ライトカラー
	MaterialData material;
	
};

#endif
