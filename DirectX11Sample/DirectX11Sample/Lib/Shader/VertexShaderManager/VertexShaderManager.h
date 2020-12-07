#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include<map>
#include<vector>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/VertexShader/VertexShader.h"
#include"../ConstantShader/ConstantShader.h"
#include"../Factory/VSFactoryBase/VSFactoryBase.h"



/**
* @class VertexShaderManager
* @brief ���_�V�F�[�_�[���Ǘ�����N���X
*/
class VertexShaderManager : public Singleton<VertexShaderManager> {
public:


	/**
	* @brief �t�����h
	*/
	friend class Singleton<VertexShaderManager>;


	/**
	* @brief �R���X�g���N�^
	*/
	VertexShaderManager();


	/**
	* @brief �f�X�g���N�^
	*/
	~VertexShaderManager();


	/**
	* @brief �V�F�[�_�t�@�C������
	*/
	bool Create(
		const std::string& cso_file_name,
		ConstantShader::VSType register_type
	);


	/**
	* @brief �V�F�[�_�[�t�@�C����j��
	*/
	void Destroy(
		ConstantShader::VSType register_type
	);


	/**
	* @brief �V�F�[�_�[�t�@�C����S�č폜
	*/
	void DestroyEverything();


	/**
	* @brief �V�F�[�_�[�t�@�C���擾
	*/
	VertexShader* GetPtr(
		ConstantShader::VSType type
	);


private:


	//! �o�[�e�b�N�X�V�F�[�_�[
	std::map<ConstantShader::VSType,VertexShader*>mp_vs_list;

	//! �H�ꃊ�X�g
	std::vector<std::unique_ptr<VSFactoryBase>>mp_vs_factory_list;
};

#endif
