#ifndef CONSTANT_SHADER_H_
#define CONSTANT_SHADER_H_



namespace ConstantShader {


	/**
	* @enum Type
	* @brief 頂点シェーダーの種類
	*/
	enum class VSType {
		NORMAL,
		VS3D,
		VARIOUS_LIGHT,
		TOTAL,
	};


	/**
	* @enum Type
	* @brief 頂点シェーダーの種類
	*/
	enum class PSType {
		NORMAL,
		VARIOUS_LIGHT,
		TOTAL,
	};
}

#endif
