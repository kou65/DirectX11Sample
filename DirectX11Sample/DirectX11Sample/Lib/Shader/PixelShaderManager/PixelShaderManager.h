
#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include<map>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/PixelShader/PixelShader.h"


/**
* @class PixelShaderManager
* @brief ���_�V�F�[�_�[���Ǘ�����N���X
*/
class PixelShaderManager {
public:

	/**
	* @enum Type
	* @brief ���_�V�F�[�_�[�̎��
	*/
	enum class Type {
		NORMAL,
	};

private:

	//! �s�N�Z���V�F�[�_�[�Ǘ���
	std::map<Type, std::unique_ptr<PixelShader>>mp_ps_list;
};

#endif
