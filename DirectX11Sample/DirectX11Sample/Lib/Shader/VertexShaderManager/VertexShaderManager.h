#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include<map>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/VertexShader/VertexShader.h"


/**
* @class VertexShaderManager
* @brief ���_�V�F�[�_�[���Ǘ�����N���X
*/
class VertexShaderManager {
public:

	/**
	* @enum Type
	* @brief ���_�V�F�[�_�[�̎��
	*/
	enum class Type {
		NORMAL,
	};

private:

	std::map<Type, std::unique_ptr<VertexShader>>mp_vs_list;
};

#endif
