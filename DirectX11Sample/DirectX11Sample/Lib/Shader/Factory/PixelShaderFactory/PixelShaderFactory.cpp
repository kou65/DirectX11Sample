#include"PixelShaderFactory.h"
#include"../../ShaderProcess/PixelShader/PixelShader.h"



PixelShader* PixelShaderFactory::Create(
	ConstantShader::PSType ps_type
) {

	switch (ps_type) {

	case ConstantShader::PSType::NORMAL:
		return new PixelShader();


	default:
		// 生成物なし
		return nullptr;
	}

	return nullptr;
}
