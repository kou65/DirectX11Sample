#include"VertexShaderFactory.h"
#include"../../ShaderProcess/VS3D/VS3D.h"



VertexShader* VertexShaderFactory::Create(
	ConstShader::VSType vs_type
) {

	switch (vs_type)
	{

	case ConstShader::VSType::NORMAL:
		return new VertexShader();

	case ConstShader::VSType::VS3D:
		return new VS3D();

	default:
		// 生成物なし
		return nullptr;
	}

	// 生成物なし
	return nullptr;
}