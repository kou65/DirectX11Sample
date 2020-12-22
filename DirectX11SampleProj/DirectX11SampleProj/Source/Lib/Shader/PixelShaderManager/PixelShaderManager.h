#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include<map>
#include<memory>
#include<vector>

#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/PixelShader/PixelShader.h"
#include"../Factory/PSFactoryBase/PSFactoryBase.h"



/**
* @class PixelShaderManager
* @brief ���_�V�F�[�_�[���Ǘ�����N���X
*/
class PixelShaderManager : public Singleton<PixelShaderManager> {
public:


	friend class Singleton<PixelShaderManager>;


	/**
	* @brief �R���X�g���N�^
	*/
	PixelShaderManager();


	/**
	* @brief �f�X�g���N�^
	*/
	~PixelShaderManager();


	/**
	* @brief �V�F�[�_�t�@�C������
	*/
	bool Create(
		const std::string& cso_file_name,
		ConstShader::PSType register_type
	);


	/**
	* @brief �V�F�[�_�[�t�@�C����j��
	*/
	void Destroy(
		ConstShader::PSType register_type
	);


	/**
	* @brief �V�F�[�_�[�t�@�C����S�č폜
	*/
	void DestroyEverything();


	/**
	* @brief �V�F�[�_�[�t�@�C���擾
	*/
	PixelShader* GetPtr(
		ConstShader::PSType type
	);


private:


	//! �s�N�Z���V�F�[�_�[�Ǘ���
	std::map<ConstShader::PSType,PixelShader*>mp_ps_list;

	//! �s�N�Z���V�F�[�_�[�����҃��X�g
	std::vector<std::unique_ptr<PSFactoryBase>>mp_ps_factory_list;


};

#endif
