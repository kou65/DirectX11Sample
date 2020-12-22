#ifndef VERTEX_SHADER_FACTORY_H_
#define VERTEX_SHADER_FACTORY_H_



#include"../../ConstShader/ConstShader.h"
#include"../../ShaderProcess/VertexShader/VertexShader.h"
#include"../VSFactoryBase/VSFactoryBase.h"



/**
* @brief ���_�V�F�[�_�[������
*/
class VertexShaderFactory : public VSFactoryBase{
public:

	VertexShader* Create(
		ConstShader::VSType vs_type
	)override;
};

#endif
