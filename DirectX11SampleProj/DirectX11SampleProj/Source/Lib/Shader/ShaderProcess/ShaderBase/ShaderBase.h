#ifndef SHADER_BASE_H_
#define SHADER_BASE_H_



#include<d3d11.h>
#include<stdio.h>
#include<string>
#include<wrl.h>
#include<vector>
#include<map>
#include"../../../Buffer/ConstBuffer/ConstBuffer.h"



using namespace Microsoft::WRL;



/**
* @class ShaderBase
* @brief Shader��base�N���X
*/
class ShaderBase {
public:


	/**
	* @brief �R���X�g���N�^
	*/
	ShaderBase();


	/**
	* @brief ���z�f�X�g���N�^
	*/
	virtual ~ShaderBase();


	/**
	* @brief Create �쐬
	* @param[out] p_device �f�o�C�X�|�C���^
	* @param[in] file_name �t�@�C����
	*/
	virtual bool Create(
		ID3D11Device*p_device,
		const std::string&file_name
	);


	/**
	* @brief �f�[�^
	*/
	inline const char* GetData()
	{
		return mp_data;
	}


	/**
	* @brief �T�C�Y
	*/
	inline long GetSize()
	{
		return m_size;
	}


	/**
	* @brief �萔�o�b�t�@��Ԃ�
	*/
	ID3D11Buffer *GetConstBuffer(
		const int&slot_number
	);


	/**
	* @brief �萔�o�b�t�@�쐬
	* @return ���łɐ�������Ă���Ȃ�false ����������true
	*/
	bool CreateConstBuffer(
		const int& slot_number,
		const UINT& buffer_size
	);


protected:


	/**
	* @brief �t�@�C���ǂݍ���
	* @param[in] file_name
	* @return int �t�@�C���T�C�Y��Ԃ�
	*/
	int LoadFile(
		const std::string& file_name
	);


protected:


	/**
	* @brief �^�̋��p�� �ǂ��炩�̌^���g����
	*/
	union Interface
	{
		~Interface() {};

		//! ���_�V�F�[�_�[
		ID3D11VertexShader * p_vs;

		//! �s�N�Z���V�F�[�_�[
		ID3D11PixelShader * p_ps;
	};

	//! �t�@�C���f�[�^
	char * mp_data;

	//! �t�@�C���T�C�Y
	long m_size;

	//! �萔�o�b�t�@���X�g
	std::vector<ConstBuffer>m_const_buffer_list;


};

#endif