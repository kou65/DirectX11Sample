#include"Camera3D.h"
#include"../Math/Math.h"



Camera3D::Camera3D() {

	m_degree = XMFLOAT3(0.f, 0.f, 0.f);
	m_eye = XMFLOAT3(10.f, 2.f, -2.f);
	m_focus = XMFLOAT3(0.f, 0.f, 1.f);
	m_up = XMFLOAT3(0.f, 1.f, 0.f);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_view_mat.m[i][j] = 0.f;
			m_proj_mat.m[i][j] = 0.f;
			
		}
	}

	m_proj_mat =
		XMFLOAT4X4();

	m_view_mat =
		XMFLOAT4X4();

	m_move.x = 0.f;
	m_move.y = 0.f;
	m_move.z = 0.f;
}


void Camera3D::Update() {


	// 横回転
	//RotationSinCos(
	//	m_eye.x,
	//	m_eye.y,
	//	m_eye.z,
	//	m_degree.y,
	//	m_degree.x
	//);

	// 一人称
	FPS();

	// ビュー変換
	ConvertView();

	// 射影変換
	ConvertProjection(
		1920,
		1080
	);

}


void Camera3D::FPS() {


	// 回転 
	XMMATRIX rot_mat_x = XMMatrixRotationX(
		m_degree.x
	);

	XMMATRIX rot_mat_y = XMMatrixRotationY(
		m_degree.y
	);

	XMMATRIX rot_mat_z = XMMatrixRotationZ(
		m_degree.z
	);

	// 回転行列作成
	XMMATRIX rot_mat_total =
	rot_mat_z * rot_mat_y * rot_mat_x;


	XMVECTOR move = 
		XMVectorSet(m_move.x,m_move.y,m_move.z,1.f);

	// 移動ベクトル正規化
	move =
	XMVector3Normalize(move);


	// 移動ベクトル * 現在の回転方向
	move =
	XMVector3TransformNormal(move,rot_mat_y);

	XMFLOAT3 v_move;

	// 視点を動かす
	Math::ConvertVec::XMVECTORToXMFLOAT3(
		&v_move,
		move
	);

	m_eye.x += v_move.x;
	m_eye.y += v_move.y;
	m_eye.z += v_move.z;

	// 移動
	XMMATRIX trans_mat = XMMatrixTranslation(
		m_eye.x,
		m_eye.y,
		m_eye.z
	);

	// 回転行列 * 移動行列
	//trans_mat = rot_mat_total * trans_mat;

	m_move.x = 0.f;
	m_move.y = 0.f;
	m_move.z = 0.f;

	XMVECTOR mult_v;
	
	mult_v =
		XMVectorSet(0.f,0.f,0.f,0.f);
	
	XMVECTOR trans_v = 
		XMVectorSet(0.f,0.f,0.f,0.f);
	
	// 行列からXMVECTOR
	Math::TSMatMultVec::TSXMVector3(
		&trans_v,
		mult_v,
		trans_mat
	);

	
	// 視点を動かす
	Math::ConvertVec::XMVECTORToXMFLOAT3(&m_eye, trans_v);
	
	// 注視点への方向ベクトル
	XMVECTOR dir =
		XMVectorSet(0.f, 0.f, 1.f, 0.f);

	XMVECTOR normal_trans =
	XMVector3Normalize(trans_v);
	
	// 方向ベクトルの回転
	Math::TSMatMultVec::TSXMVector3(
		&dir,
		dir,
		rot_mat_y
	);


	XMVector3TransformNormal(dir, rot_mat_y);
	
	// 現在地 + 現方向ベクトル
	XMVECTOR trans_dir =
		trans_v + dir;
	
	// 注視点更新
	Math::ConvertVec::XMVECTORToXMFLOAT3(
		&m_focus,
		trans_dir
	);

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


void Camera3D::ConvertProjection(
float aspect_width,
float aspect_height
) {

	// プロジェクションの角度
	constexpr float fov_angle =
		XMConvertToRadians(45.f);

	// アスペクト比
	float aspect =
		aspect_width / aspect_height;

	// 描画クリッピング距離
	float near_z = 0.1f;
	float far_z = 100.f;

	XMMATRIX proj_matrix =
		XMMatrixPerspectiveFovLH(
			fov_angle,
			aspect,
			near_z,
			far_z
		);

	XMStoreFloat4x4(
		&m_proj_mat,
		XMMatrixTranspose(proj_matrix)
	);
}


void Camera3D::ConvertView() {


	// ビューの位置座標
	XMVECTOR eye =
		XMVectorSet(m_eye.x,m_eye.y,m_eye.z, 0.f);

	// 注視点
	XMVECTOR focus =
		XMVectorSet(m_focus.x, m_focus.y, m_focus.z, 0.f);

	// 上方向
	XMVECTOR up =
		XMVectorSet(m_up.x, m_up.y, m_up.z, 0.f);

	// ビュー行列
	XMMATRIX view_matrix =
		XMMatrixLookAtLH(eye, focus, up);

	XMStoreFloat4x4(
		&m_view_mat,
		XMMatrixTranspose(view_matrix)
	);
}


void Camera3D::AddPos(XMFLOAT3 add_pos) {

	m_move.x += add_pos.x;
	m_move.y += add_pos.y;
	m_move.z += add_pos.z;
}


void Camera3D::AddDegree(const XMFLOAT3 &add_degree) {

	m_degree.x += add_degree.x;
	m_degree.y += add_degree.y;
	m_degree.z += add_degree.z;
}


XMFLOAT3 Camera3D::GetPos() {
	return m_eye;
}


XMFLOAT4X4 Camera3D::GetViewTransposeMatrix() {

	return m_view_mat;
}


XMFLOAT4X4 Camera3D::GetProjTransposeMatrix() {

	return m_proj_mat;
}