#include"VertexShaderFactory.h"
#include"../../ShaderProcess/VS3D/VS3D.h"



VertexShader* VertexShaderFactory::Create(
	ConstantShader::VSType vs_type
) {

	switch (vs_type)
	{

	case ConstantShader::VSType::NORMAL:
		return new VertexShader();

	case ConstantShader::VSType::VS3D:
		return new VS3D();

	default:
		// 生成物なし
		return nullptr;
	}

	// 生成物なし
	return nullptr;
}