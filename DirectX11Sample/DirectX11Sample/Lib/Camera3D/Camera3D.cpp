#include"Camera3D.h"
#include"../Math/Math.h"



void Camera3D::FPS() {

}


void Camera3D::TPS() {

}





float Camera3D::GetHAngle(
const XMFLOAT3&target_pos
) {

	// 注視点への方向ベクトルを求める
	XMFLOAT3 dir;

	dir.x =
	target_pos.x - m_eye.x;
	dir.y =
		target_pos.y - m_eye.y;
	dir.z =
		target_pos.z - m_eye.z;

	// hangleXZ平面での角度を求める
	// x z 0 1を正面としている
	// 多分dir.zは-いらない(左手系なので)
	float deg =
	atan2f(-dir.z, dir.x);

	return deg;
}


float Camera3D::GetVAngle(
	const XMFLOAT3& target_pos
) {

	
	// 注視点への方向ベクトルを求める
	XMFLOAT3 dir;

	dir.x =
		target_pos.x - m_eye.x;
	dir.y =
		target_pos.y - m_eye.y;
	dir.z =
		target_pos.z - m_eye.z;

	// xz平面における距離
	float front_f;

	XMFLOAT3 front_v = dir;

	// XZ平面での距離なのでYはいらない
	front_v.y = 0;

	// 距離を出す
	front_f = Math::GetLength(front_v);


	// Y軸とXZ平面の前方方向との角度を求める
	float deg = atan2f(-dir.y, front_f);

	return deg;
}



void Camera3D::NormalConvFPS() {


	// 横回転
	RotationSinCos(m_pos.x,m_pos.y,m_pos.z,m_rotation.y);


}


void Camera3D::RotationSinCos(
float &x,
float &y,
float &z,
float y_rot_deg,
float x_rot_deg
) {

	// 横回転
	Math::Rotation2D(Math::DegreesToRad(y_rot_deg),x,z,x,z);

	// 縦回転
	//Math::Rotation2D(Math::DegreesToRad(0), z, y, z, y);
}