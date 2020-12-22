#ifndef MODEL_PRIMITIVE_H_
#define MODEL_PRIMITIVE_H_



#include<vector>
#include<map>
#include<string>
#include"../MeshPrimitive/MeshPrimitive.h"
#include"../../MaterialData/MaterialData.h"
#include"../../Shader/ConstShader/ConstShader.h"



/**
* @brief ���f�����q�N���X
*/
struct Model {
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Model() {};


	/**
	* @brief ���b�V����Ԃ�
	*/
	MeshPrimitive GetMesh(const int&mesh_count) {
		return m_mesh_list[mesh_count];
	}


	/**
	* @brief �ő僁�b�V�����X�g�T�C�Y��Ԃ�
	*/
	size_t GetMeshCount() {
		return m_mesh_list.size();
	}


	/**
	* @brief ���b�V���ǉ�
	*/
	void AddMesh(MeshPrimitive p_input_mesh) {

		m_mesh_list.emplace_back(p_input_mesh);
	}


	/**
	* @brief �V�F�[�_�[vs���ʔԍ��Z�b�g
	*/
	void SetVSType(const ConstShader::VSType&vs_type) {
		m_vs_type = vs_type;
	}


	/**
	* @brief �V�F�[�_�[ps���ʔԍ��Z�b�g
	*/
	void SetPSType(const ConstShader::PSType& ps_type) {
		m_ps_type = ps_type;
	}


	/**
	* @brief �V�F�[�_�[vs���ʔԍ���Ԃ�
	*/
	ConstShader::VSType GetVSType() {
		return m_vs_type;
	}


	/**
	* @brief �V�F�[�_�[ps���ʔԍ���Ԃ�
	*/
	ConstShader::PSType GetPSType() {
		return m_ps_type;
	}


private:


	//! ���b�V���z��
	std::vector<MeshPrimitive>m_mesh_list;

	//! �V�F�[�_�[vs���ʔԍ������b�V���ɖ��ߍ���
	ConstShader::VSType m_vs_type;

	//! �V�F�[�_�[ps���ʔԍ������b�V���ɖ��ߍ���
	ConstShader::PSType m_ps_type;


};
#endif
