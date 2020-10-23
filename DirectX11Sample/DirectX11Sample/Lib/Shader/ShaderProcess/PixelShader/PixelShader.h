#ifndef PIXEL_SHADER_H_
#define PIXEL_SHADER_H_

#include"../ShaderBase/ShaderBase.h"


class PixelShader : public ShaderBase{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	PixelShader();


	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~PixelShader();


	/**
	* @brief �쐬
	*/
	virtual bool Create(
		ID3D11Device* p_device,
		const std::string& file_name
	);


	/**
	* @brief �C���^�[�t�F�[�Xptr��Ԃ�
	*/
	ID3D11PixelShader *GetInterfacePtr();

private:

	ID3D11PixelShader *mp_ps;
};

#endif
