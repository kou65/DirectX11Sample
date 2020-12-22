#ifndef VS_FACTORY_BASE_H_
#define VS_FACTORY_BASE_H_
#include"../../ShaderProcess/VertexShader/VertexShader.h"
#include"../../ConstShader/ConstShader.h"



/**
* @brief ���_�V�F�[�_�[���
*/
class VSFactoryBase {
public:


	/**
	* @brief ���z�f�X�g���N�^
	*/
	virtual ~VSFactoryBase() {};


	/**
	* @brief �e���_�V�F�[�_�[�𐶐����郁�\�b�h
	*/
	virtual VertexShader *Create(
		ConstShader::VSType vs_type
	) = 0;


};


#endif
