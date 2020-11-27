#ifndef PRIMITIVE_RENDERER_H_
#define PRIMITIVE_RENDERER_H_


#include<memory>
#include<DirectXMath.h>
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../Polygon/PolygonPrimitive/PolygonPrimitive.h"
#include"../Polygon/MeshPrimitive/MeshPrimitive.h"
#include"../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../Shader/ConstantShader/ConstantShader.h"



using namespace DirectX;



/**
* @class PrimitiveRenderer
* @brief ポリゴンを描画するシングルトンクラス
*/
class PrimitiveRenderer : public Singleton<PrimitiveRenderer>{
public:

	// インスタンスアクセス許可
	friend Singleton<PrimitiveRenderer>;

public:


	/**
	* @brief 初期化
	*/
	bool Create();


	/**
	* @brief ポリゴン描画
	*/
	void RenderingPolygon(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		PolygonPrimitive* pol,
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
	);


	/**
	* @brief デバイスの情報を使ったポリゴン描画
	*/
	void RenderingPolygonByDeviceView(
		PolygonPrimitive* pol,
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
	);


	/**
	* @brief デバイスの情報を使ったメッシュ描画
	*/
	void RenderingMesh(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		MeshPrimitive* mesh,
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
	);


	/**
	* @brief デバイスの情報を使ったメッシュ描画
	*/
	void RenderingMeshByDeviceView(
		MeshPrimitive* mesh,
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
	);


	/**
	* @brief 後始末
	*/
	void ClearRenderingInfo(
		ID3D11DeviceContext* p_context
	);


	/**
	* @brief セットアップラスタライザ
	*/
	void SetUpRasterizer();


private:

	/**
	* @brief 隠しコンストラクタ
	*/
	PrimitiveRenderer();

private:


	//! ラスタライザステート
	ID3D11RasterizerState *mp_ras_state;


};


#endif
