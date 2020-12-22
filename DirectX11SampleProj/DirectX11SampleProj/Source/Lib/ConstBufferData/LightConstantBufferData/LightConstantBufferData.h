#ifndef LIGHT_CONSTANT_BUFFER_DATA_H_
#define LIGHT_CONSTANT_BUFFER_DATA_H_


#include"../../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../../LightData/LightData.h"



/**
* @brief ���C�g�V�F�[�_�[�̒萔�f�[�^
*/
struct LightConstantBufferData {

	TS3DMatrixData trans3d_data; // 3d�ϊ��f�[�^
	LightData light;             // ���C�g�f�[�^
	XMFLOAT4 camera_pos;         // �J�������W

};


#endif
