#ifndef VERTEX_SHADER_FACTORY_H_
#define VERTEX_SHADER_FACTORY_H_



#include"../../ConstantShader/ConstantShader.h"
#include"../../ShaderProcess/VertexShader/VertexShader.h"
#include"../VSFactoryBase/VSFactoryBase.h"



/**
* @brief ���_�V�F�[�_�[������
*/
class VertexShaderFactory : public VSFactoryBase{
public:

	VertexShader* Create(
		ConstantShader::VSType vs_type
	)override;
};

#endif
