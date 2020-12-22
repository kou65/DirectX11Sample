#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include<d3d11.h>
#include"../ShaderBase/ShaderBase.h"
#include"../../InputDescInfo/InputDescInfo.h"



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
	bool Create(
		ID3D11Device* p_device,
		const std::string& file_name
	)override;


	// MEMO �C���v�b�g�f�X�N�����܂Ƃ߂Ă���N���X��namespace�����?
	/**
	* @brief �C���v�b�g���C�A�E�g�̍쐬
	*/
	bool CreateInputLayout(
		const InputDescInfo& p_input_desc
	);


	/**
	* @brief �C���^�[�t�F�[�X
	*/
	ID3D11VertexShader* GetInterfacePtr();


	/**
	* @brief �C���v�b�g���C�A�E�g��Ԃ�
	*/
	ID3D11InputLayout* GetInputLayoutPtr();


private:

	//! ���_�V�F�[�_�[�o�b�t�@
	ID3D11VertexShader *mp_vs;

	//! �C���v�b�g���C�A�E�g (MEMO VertexShader��h�����ăC���v�b�g���C�A�E�g�̍쐬���Ă����ޗp�ɂ���?)
	ID3D11InputLayout* mp_input_layout;
};

#endif