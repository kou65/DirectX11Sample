#ifndef PIXEL_SHADER_FACTORY_H_
#define PIXEL_SHADER_FACTORY_H_


#include"../PSFactoryBase/PSFactoryBase.h"


/**
* @brief �s�N�Z���V�F�[�_�[������
*/
class PixelShaderFactory : public PSFactoryBase{
public:


	PixelShader* Create(
		ConstShader::PSType ps_type
	)override;


};

#endif
