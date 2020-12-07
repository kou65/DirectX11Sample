#ifndef LIGHT_H_
#define LIGHT_H_


#include"../LightConstBuffer/LightConstBuffer.h"
#include"../Camera3D/Camera3D.h"
#include"../TransformMatrixData3D/TransformMatrixData3D.h"



/**
* @brief ���C�g�V�F�[�_�[�𐧌䂷�郉�C�g�N���X
*/
class Light {
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Light() {}


	/**
	* @brief �p�����[�^�Z�b�g
	*/
	void SetParameter(
		Camera3D* p_camera,
		const TS3DMatrixData& ts_data
	);


private:

	//! ���C�g�f�[�^
	LightConstBuffer m_light_data;

};

#endif
