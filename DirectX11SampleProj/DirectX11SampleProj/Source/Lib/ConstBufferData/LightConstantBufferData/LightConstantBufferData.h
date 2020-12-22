#ifndef LIGHT_CONSTANT_BUFFER_DATA_H_
#define LIGHT_CONSTANT_BUFFER_DATA_H_


#include"../../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../../LightData/LightData.h"



/**
* @brief ライトシェーダーの定数データ
*/
struct LightConstantBufferData {

	TS3DMatrixData trans3d_data; // 3d変換データ
	LightData light;             // ライトデータ
	XMFLOAT4 camera_pos;         // カメラ座標

};


#endif
