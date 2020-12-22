#ifndef LIGHT_DATA_H_
#define LIGHT_DATA_H_


#include<DirectXMath.h>
#include"../MaterialData/MaterialData.h"


using namespace DirectX;


/**
* @brief ���C�g�f�[�^���܂ލ\����
*/
struct LightData {


	XMFLOAT4 light_pos;     // ���C�g���W
	XMFLOAT4 light_vector;  // ���C�g����
	XMFLOAT4 light_color;   // ���C�g�J���[
	MaterialData material;
	
};

#endif
