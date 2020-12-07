#ifndef LIGHT_H_
#define LIGHT_H_


#include"../LightConstBuffer/LightConstBuffer.h"
#include"../Camera3D/Camera3D.h"
#include"../TransformMatrixData3D/TransformMatrixData3D.h"



/**
* @brief ライトシェーダーを制御するライトクラス
*/
class Light {
public:


	/**
	* @brief コンストラクタ
	*/
	Light() {}


	/**
	* @brief パラメータセット
	*/
	void SetParameter(
		Camera3D* p_camera,
		const TS3DMatrixData& ts_data
	);


private:

	//! ライトデータ
	LightConstBuffer m_light_data;

};

#endif
