#ifndef CAMERA_3D_H_
#define CAMERA_3D_H_




#include<DirectXMath.h>
#include"../SingletonTemplate/SingletonTemplate.h"


using namespace DirectX;


/**
* @brief カメラ3D
*/
class Camera3D : public Singleton<Camera3D>{
public:


	friend class Singleton<Camera3D>;


	/**
	* @brief fpsモード
	*/
	void FPS();


	/**
	* @brief tpsモード
	*/
	void TPS();


private:

	void NormalConvFPS();

	void RotationSinCos(
		float& x,
		float& y,
		float& z,
		float y_rot_deg,
		float x_rot_deg
	);

	float GetHAngle(
		const XMFLOAT3& target_pos
	);

	float GetVAngle(
		const XMFLOAT3& target_pos
	);


private:

	XMFLOAT4X4 m_world_mat;
	XMFLOAT4X4 m_rotation_mat;
	XMFLOAT3 m_pos;
	XMFLOAT3 m_rotation;

	// 基本カメラ情報
	XMFLOAT3 m_eye;
	XMFLOAT3 focus;
	XMFLOAT3 up;
};



#endif
