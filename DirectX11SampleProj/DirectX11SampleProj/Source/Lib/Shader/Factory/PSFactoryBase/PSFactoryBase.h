#ifndef PS_FACTORY_BASE_H_
#define PS_FACTORY_BASE_H_



#include"../../ShaderProcess/PixelShader/PixelShader.h"
#include"../../ConstShader/ConstShader.h"


/**
* @brief psファクトリ基底
*/
class PSFactoryBase {
public:


	/**
	* @brief 仮想デストラクタ
	*/
	virtual ~PSFactoryBase() {};


	/**
	* @brief 各頂点シェーダーを生成するメソッド
	*/
	virtual PixelShader* Create(
		ConstShader::PSType vs_type
	) = 0;


};


#endif
