#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include<d3d11.h>
#include"../ShaderBase/ShaderBase.h"
#include"../../InputDescInfo/InputDescInfo.h"



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
	bool Create(
		ID3D11Device* p_device,
		const std::string& file_name
	)override;


	// MEMO インプットデスク情報をまとめてあるクラスやnamespaceを作る?
	/**
	* @brief インプットレイアウトの作成
	*/
	bool CreateInputLayout(
		const InputDescInfo& p_input_desc
	);


	/**
	* @brief インターフェース
	*/
	ID3D11VertexShader* GetInterfacePtr();


	/**
	* @brief インプットレイアウトを返す
	*/
	ID3D11InputLayout* GetInputLayoutPtr();


private:

	//! 頂点シェーダーバッファ
	ID3D11VertexShader *mp_vs;

	//! インプットレイアウト (MEMO VertexShaderを派生してインプットレイアウトの作成を焼きこむ用にする?)
	ID3D11InputLayout* mp_input_layout;
};

#endif