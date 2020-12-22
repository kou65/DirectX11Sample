#ifndef LIGHT_CONST_BUFFER_H_
#define LIGHT_CONST_BUFFER_H_



#include<DirectXMath.h>


using namespace DirectX;


/**
* @brief ���C�g�萔�o�b�t�@
*/
struct LightConstBuffer {

	XMFLOAT4X4	World;				// ���[���h�ϊ��s��
	XMFLOAT4X4	View;				// �r���[�ϊ��s��
	XMFLOAT4X4	Projection;			// �����ˉe�ϊ��s��
	XMFLOAT4	CameraPos;			// �J�������W
	XMFLOAT4	LightPos;			// ���C�g���W
	XMFLOAT4	LightVector;		// ���C�g����
	XMFLOAT4	LightColor;			// ���C�g�J���[
	XMFLOAT4	MaterialAmbient;	// �A���r�G���g
	XMFLOAT4	MaterialDiffuse;	// �f�B�t���[�Y
	XMFLOAT4	MaterialSpecular;	// �X�y�L�����[

};


#endif
