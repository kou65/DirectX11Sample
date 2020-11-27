#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include<d3d11.h>
#include"../ShaderBase/ShaderBase.h"


/**
* @class VertexShader
* @brief ���_�V�F�[�_�[
*/
class VertexShader : public ShaderBase {
public:


	/**
	* @brief �R���X�g���N�^
	*/
	VertexShader();


	/**
	* @brief ���z�f�X�g���N�^
	*/
	virtual ~VertexShader();


	/**
	* @brief ���_�V�F�[�_�[�쐬
	*/
	virtual bool Create(
		ID3D11Device* p_device,
		const std::string& file_name
	);


	/**
	* @brief �C���^�[�t�F�[�X
	*/
	ID3D11VertexShader* GetInterfacePtr();


private:

	//! ���_�V�F�[�_�[�o�b�t�@
	ID3D11VertexShader *mp_vs;
};

#endif