#ifndef PIXEL_SHADER_FACTORY_H_
#define PIXEL_SHADER_FACTORY_H_


#include"../PSFactoryBase/PSFactoryBase.h"


/**
* @brief ピクセルシェーダー生成者
*/
class PixelShaderFactory : public PSFactoryBase{
public:


	PixelShader* Create(
		ConstShader::PSType ps_type
	)override;


};

#endif
