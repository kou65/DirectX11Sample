#ifndef SHADER_BASE_H_
#define SHADER_BASE_H_

#include<d3d11.h>
#include<stdio.h>
#include<string>
#include<wrl.h>


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
	* @brief Create �쐬
	* @param[out] p_device �f�o�C�X�|�C���^
	* @param[in] file_name �t�@�C����
	*/
	virtual bool Create(
		ID3D11Device*p_device,
		const std::string&file_name
	);


	inline const char* GetData()
	{
		return mp_data;
	}

	inline long GetSize()
	{
		return m_size;
	}

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

		ID3D11VertexShader *p_vs;
		ID3D11PixelShader *p_ps;
	};

	//! �t�@�C���f�[�^
	char* mp_data;

	//! �t�@�C���T�C�Y
	long m_size;
};

#endif
