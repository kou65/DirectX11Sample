#ifndef TRANSFORM_MATRIX_DATA_3D_H_
#define TRANSFORM_MATRIX_DATA_3D_H_


#include<DirectXMath.h>


using namespace DirectX;


/**
* @struct TransformMatrixData3D
* @brief 3D�ϊ��s��f�[�^�\����
*/
struct TransformMatrixData3D {

	XMFLOAT4X4 world;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;

};


#endif
