#ifndef CAMERA_3D_H_
#define CAMERA_3D_H_

#include<DirectXMath.h>



using namespace DirectX;



/**
* @brief カメラ3D
*/
class Camera3D{
public:


	/**
	* @brief コンストラクタ
	*/
	Camera3D();


	/**
	* @brief 更新
	*/
	void Update();


	/**
	* @brief fpsモード
	*/
	void FPS();


	/**
	* @brief tpsモード
	*/
	void TPS();


	/**
	* @brief 回転値を加算
	*/
	void AddDegree(const XMFLOAT3 &add_degree);


	/**
	* @brief 位置を加算
	*/
	void AddPos(XMFLOAT3 add_pos);


	/**
	* @brief 位置を返す
	*/
	XMFLOAT3 GetPos();


	/**
	* @brief ビュー行列を返す
	*/
	XMFLOAT4X4 GetViewTransposeMatrix();


	/**
	* @brief 射影行列を返す
	*/
	XMFLOAT4X4 GetProjTransposeMatrix();


private:


	/**
	* @brief 射影変換
	*/
	void ConvertProjection(
		float aspect_width,
		float aspect_height
	);


	/**
	* @brief ビュー変換
	*/
	void ConvertView();


	// 水平アングル
	float GetHAngle(
		const XMFLOAT3& target_pos
	);


	// 縦方面アングル
	float GetVAngle(
		const XMFLOAT3& target_pos
	);


private:


	/**
	* @brief 二次回転
	*/
	void RotationSinCos(
		float& x,
		float& y,
		float& z,
		float y_rot_deg,
		float x_rot_deg
	);


private:

	
	//! プロジェクション
	XMFLOAT4X4 m_proj_mat;

	//! ビュー
	XMFLOAT4X4 m_view_mat;

	//! 角度
	XMFLOAT3 m_degree;

	//! 視点位置
	XMFLOAT3 m_eye;

	//! 注視点
	XMFLOAT3 m_focus;

	//! 上方向ベクトル
	XMFLOAT3 m_up;

	//! 移動ベクトル
	XMFLOAT3 m_move;
};



#endif
