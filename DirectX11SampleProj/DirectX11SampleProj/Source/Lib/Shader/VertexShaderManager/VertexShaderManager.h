#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include<map>
#include<vector>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/VertexShader/VertexShader.h"
#include"../Factory/VSFactoryBase/VSFactoryBase.h"
#include"../InputDescInfo/InputDescInfo.h"




// MEMO �V�F�[�_�[�𕪂��ĊǗ����Ȃ��Ă� 

// VertexShaderManager::GetInstance()->Create(
//   VERTEX                                  // �V�F�[�_�[�̎��
// 	 "CSO/VertexShader.cso",                 // �w��CSO�t�@�C���̓ǂݍ���(���ꂪ�ǂ�hlsl�t�@�C�����m�F���ēǂݍ���)
// 	 ConstShader::VSType::NORMAL          // ���ʔԍ�(������ɂ��邩)
// );

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
		const std::string&cso_file_name,
		const ConstShader::VSType&register_type,
		const ConstShader::InputLayout::InputType input_layout_type
	);


	/**
	* @brief �V�F�[�_�[�t�@�C����j��
	*/
	void Destroy(
		const ConstShader::VSType&register_type
	);


	/**
	* @brief �V�F�[�_�[�t�@�C����S�č폜
	*/
	void DestroyEverything();


	/**
	* @brief �V�F�[�_�[�t�@�C���擾
	*/
	VertexShader* GetPtr(
		const ConstShader::VSType&type
	);


private:


	/**
	* @brief �C���v�b�g���C�A�E�g�f�X�N����������
	*/
	void SetUpInputDescList();


private:


	//! �o�[�e�b�N�X�V�F�[�_�[
	std::map<ConstShader::VSType,VertexShader*>mp_vs_list;

	//! �C���v�b�g���C�A�E�g�f�X�N���X�g
	std::map<ConstShader::InputLayout::InputType,InputDescInfo>mp_input_desc_list;

	//! �z��T�C�Y�C���v�b�g���C�A�E�g�T�C�Y���X�g

	//! �H�ꃊ�X�g
	std::vector<std::unique_ptr<VSFactoryBase>>mp_vs_factory_list;


};

#endif
