#ifndef VS_FACTORY_BASE_H_
#define VS_FACTORY_BASE_H_
#include"../../ShaderProcess/VertexShader/VertexShader.h"
#include"../../ConstantShader/ConstantShader.h"



/**
* @brief 頂点シェーダー基底
*/
class VSFactoryBase {
public:


	/**
	* @brief 仮想デストラクタ
	*/
	virtual ~VSFactoryBase() {};


	/**
	* @brief 各頂点シェーダーを生成するメソッド
	*/
	virtual VertexShader *Create(
		ConstantShader::VSType vs_type
	) = 0;


};


#endif
