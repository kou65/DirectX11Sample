#include"PixelShaderFactory.h"
#include"../../ShaderProcess/PixelShader/PixelShader.h"



PixelShader* PixelShaderFactory::Create(
	ConstShader::PSType ps_type
) {

	switch (ps_type) {

	case ConstShader::PSType::NORMAL:
		return new PixelShader();


	default:
		// 生成物なし
		return nullptr;
	}

	return nullptr;
}
