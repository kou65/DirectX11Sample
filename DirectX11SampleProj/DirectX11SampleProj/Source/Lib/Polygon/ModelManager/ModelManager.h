#ifndef MODEL_MANAGER_H_
#define MODEL_MANAGER_H_

#include<map>
#include<string>
#include"../Model/Model.h"
#include"../../MaterialData/MaterialData.h"
#include"../../Shader/ConstShader/ConstShader.h"
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../../TransformMatrixData3D/TransformMatrixData3D.h"



/**
* @brief ���f���Ǘ��҃N���X
*/
class ModelManager : public Singleton<ModelManager>{
public:


	friend class Singleton<ModelManager>;


	/**
	* @brief �t�@�C���t�H�[�}�b�g
	*/
	enum class FileFormat {
		OBJ,
	};

public:


	// MEMO ���f���̊g���q�Ŏ��ʂ��Ă��ǂ�
	/**
	* @brief ���f���t�@�C���ǂݍ���
	*/
	bool Load(
		FileFormat format,
		const std::string model_file_path,
		const std::string register_name
	);


	/**
	* @brief �S�ĕ`��
	*/
	void Draw(
		const TS3DMatrixData&ts_mat_data
	);


	/**
	* @brief ���b�V���𕔕��I�ɕ`��
	*/
	void DrawSubSet(
		Model*model,
		const int&mesh_number
	);


	/**
	* @brief index_start�ŃT�u�Z�b�g���s��
	*/
	void DrawIndexSubSet(
		Model*model,
		const int& mesh_number,
		const int& sub_set_number
	);


	/**
	* @brief vs�V�F�[�_�[�`�F���W
	* @param[in] ���ɐݒ肷�钸�_�V�F�[�_�[
	* @param[in] �o�^���Ă��郂�f����
	*/
	void ChangeVSShader(
		const ConstShader::VSType&vs_type,
		const std::string& register_name
	);


	/**
	* @brief ps�V�F�[�_�[�`�F���W
	* @param[in] ���ɐݒ肷�钸�_�V�F�[�_�[
	* @param[in] �o�^���Ă��郂�f����
	*/
	void ChangePSShader(
		const ConstShader::PSType&ps_type,
		const std::string& register_name
	);


	/**
	* @brief �S�Ẵ��f����vs�V�F�[�_�[���`�F���W
	*/
	void AllChangeVSShader(
		const ConstShader::VSType& vs_type
	);


	/**
	* @brief �S�Ẵ��f����ps�V�F�[�_�[���`�F���W
	*/
	void AllChangePSShader(
		const ConstShader::PSType& ps_type
	);


private:


	/**
	* @brief ���b�V���`��
	*/
	void DrawMesh(
		ID3D11DeviceContext*p_context,
		MeshPrimitive*mesh,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type,
		const int& index_start,
		const int& index_count,
		const int& vs_c_num = 0,
		const int& ps_c_num = 0
	);


private:


	//! ���f�����X�g(�V�F�[�_�[���Ƃɐ؂蕪����)
	std::map<std::string, Model*>mp_model_list;

};

#endif
