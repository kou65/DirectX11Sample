#ifndef LIGHT_CONST_BUFFER_H_
#define LIGHT_CONST_BUFFER_H_



#include<DirectXMath.h>


using namespace DirectX;


/**
* @brief ライト定数バッファ
*/
struct LightConstBuffer {

	XMFLOAT4X4	World;				// ワールド変換行列
	XMFLOAT4X4	View;				// ビュー変換行列
	XMFLOAT4X4	Projection;			// 透視射影変換行列
	XMFLOAT4	CameraPos;			// カメラ座標
	XMFLOAT4	LightPos;			// ライト座標
	XMFLOAT4	LightVector;		// ライト方向
	XMFLOAT4	LightColor;			// ライトカラー
	XMFLOAT4	MaterialAmbient;	// アンビエント
	XMFLOAT4	MaterialDiffuse;	// ディフューズ
	XMFLOAT4	MaterialSpecular;	// スペキュラー

};


#endif
