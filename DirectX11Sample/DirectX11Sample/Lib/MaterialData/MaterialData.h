#ifndef MATERIAL_DATA_H_
#define MATERIAL_DATA_H_



#include<DirectXMath.h>


using namespace DirectX;


/**
* @brief �}�e���A�������܂񂾃f�[�^�\����
*/
struct MaterialData {

	XMFLOAT4 ambient;   // �A���r�G���g(����)
	XMFLOAT4 diffuse;   // �f�B�t���[�Y(�g�U��)
	XMFLOAT4 specular;  // �X�y�L�����[(���ˌ�)
};

#endif
