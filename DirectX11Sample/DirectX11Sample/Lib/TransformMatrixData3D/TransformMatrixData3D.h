#ifndef TRANSFORM_MATRIX_DATA_3D_H_
#define TRANSFORM_MATRIX_DATA_3D_H_


#include<DirectXMath.h>


using namespace DirectX;


/**
* @struct TS3DMatrixData
* @brief 3D�ϊ��s��f�[�^�\����
*/
struct TS3DMatrixData {

	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;

};


#endif
