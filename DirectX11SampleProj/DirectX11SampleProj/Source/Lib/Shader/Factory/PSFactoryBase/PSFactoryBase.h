#ifndef PS_FACTORY_BASE_H_
#define PS_FACTORY_BASE_H_



#include"../../ShaderProcess/PixelShader/PixelShader.h"
#include"../../ConstShader/ConstShader.h"


/**
* @brief ps�t�@�N�g�����
*/
class PSFactoryBase {
public:


	/**
	* @brief ���z�f�X�g���N�^
	*/
	virtual ~PSFactoryBase() {};


	/**
	* @brief �e���_�V�F�[�_�[�𐶐����郁�\�b�h
	*/
	virtual PixelShader* Create(
		ConstShader::PSType vs_type
	) = 0;


};


#endif
