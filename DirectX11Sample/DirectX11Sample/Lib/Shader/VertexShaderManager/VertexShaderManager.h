#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include<map>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/VertexShader/VertexShader.h"


/**
* @class VertexShaderManager
* @brief 頂点シェーダーを管理するクラス
*/
class VertexShaderManager {
public:

	/**
	* @enum Type
	* @brief 頂点シェーダーの種類
	*/
	enum class Type {
		NORMAL,
	};

private:

	std::map<Type, std::unique_ptr<VertexShader>>mp_vs_list;
};

#endif
