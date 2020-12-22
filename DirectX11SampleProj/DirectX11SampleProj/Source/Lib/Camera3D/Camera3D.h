#ifndef CAMERA_3D_H_
#define CAMERA_3D_H_

#include<DirectXMath.h>



using namespace DirectX;



/**
* @brief �J����3D
*/
class Camera3D{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Camera3D();


	/**
	* @brief �X�V
	*/
	void Update();


	/**
	* @brief fps���[�h
	*/
	void FPS();


	/**
	* @brief tps���[�h
	*/
	void TPS();


	/**
	* @brief ��]�l�����Z
	*/
	void AddDegree(const XMFLOAT3 &add_degree);


	/**
	* @brief �ʒu�����Z
	*/
	void AddPos(XMFLOAT3 add_pos);


	/**
	* @brief �ʒu��Ԃ�
	*/
	XMFLOAT3 GetPos();


	/**
	* @brief �r���[�s���Ԃ�
	*/
	XMFLOAT4X4 GetViewTransposeMatrix();


	/**
	* @brief �ˉe�s���Ԃ�
	*/
	XMFLOAT4X4 GetProjTransposeMatrix();


private:


	/**
	* @brief �ˉe�ϊ�
	*/
	void ConvertProjection(
		float aspect_width,
		float aspect_height
	);


	/**
	* @brief �r���[�ϊ�
	*/
	void ConvertView();


	// �����A���O��
	float GetHAngle(
		const XMFLOAT3& target_pos
	);


	// �c���ʃA���O��
	float GetVAngle(
		const XMFLOAT3& target_pos
	);


private:


	/**
	* @brief �񎟉�]
	*/
	void RotationSinCos(
		float& x,
		float& y,
		float& z,
		float y_rot_deg,
		float x_rot_deg
	);


private:

	
	//! �v���W�F�N�V����
	XMFLOAT4X4 m_proj_mat;

	//! �r���[
	XMFLOAT4X4 m_view_mat;

	//! �p�x
	XMFLOAT3 m_degree;

	//! ���_�ʒu
	XMFLOAT3 m_eye;

	//! �����_
	XMFLOAT3 m_focus;

	//! ������x�N�g��
	XMFLOAT3 m_up;

	//! �ړ��x�N�g��
	XMFLOAT3 m_move;
};



#endif
