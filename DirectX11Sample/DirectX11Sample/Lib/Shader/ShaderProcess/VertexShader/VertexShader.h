#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include<d3d11.h>
#include"../ShaderBase/ShaderBase.h"


/**
* @class VertexShader
* @brief 頂点シェーダー
*/
class VertexShader : public ShaderBase {
public:


	/**
	* @brief コンストラクタ
	*/
	VertexShader();


	/**
	* @brief 仮想デストラクタ
	*/
	virtual ~VertexShader();


	/**
	* @brief 頂点シェーダー作成
	*/
	virtual bool Create(
		ID3D11Device* p_device,
		const std::string& file_name
	);


	/**
	* @brief インターフェース
	*/
	ID3D11VertexShader* GetInterfacePtr();


private:

	//! 頂点シェーダーバッファ
	ID3D11VertexShader *mp_vs;
};

#endif