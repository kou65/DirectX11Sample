
#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include<map>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/PixelShader/PixelShader.h"


/**
* @class PixelShaderManager
* @brief 頂点シェーダーを管理するクラス
*/
class PixelShaderManager {
public:

	/**
	* @enum Type
	* @brief 頂点シェーダーの種類
	*/
	enum class Type {
		NORMAL,
	};

private:

	//! ピクセルシェーダー管理者
	std::map<Type, std::unique_ptr<PixelShader>>mp_ps_list;
};

#endif
