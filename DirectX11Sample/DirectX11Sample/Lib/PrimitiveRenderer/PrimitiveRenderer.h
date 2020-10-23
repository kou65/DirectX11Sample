#ifndef PRIMITIVE_RENDERER_H_
#define PRIMITIVE_RENDERER_H_


#include<memory>
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../Polygon/PolygonPrimitive/PolygonPrimitive.h"
#include"../Polygon/MeshPrimitive/MeshPrimitive.h"
#include"../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../Shader/ShaderProcess/PixelShader/PixelShader.h"



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
	bool Init();


	/**
	* @brief ポリゴン描画
	*/
	void RenderingPolygon(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		PolygonPrimitive* pol
	);


	/**
	* @brief デバイスの情報を使ったポリゴン描画
	*/
	void RenderingPolygonDev(
		PolygonPrimitive* pol
	);


	/**
	* @brief デバイスの情報を使ったメッシュ描画
	*/
	void RenderingMesh(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		MeshPrimitive* mesh
	);

	/**
	* @brief デバイスの情報を使ったメッシュ描画
	*/
	void RenderingMeshDev(
		MeshPrimitive* mesh
	);


	/**
	* @brief セットアップラスタライザ
	*/
	void SetUpRasterizer();


	VertexShader* GetPtrVertexShader(){
		return mp_vs.get();
	}

private:

	/**
	* @brief 隠しコンストラクタ
	*/
	PrimitiveRenderer();

private:

	//! 頂点シェーダー
	std::unique_ptr<VertexShader>mp_vs;

	//! ピクセルシェーダー
	std::unique_ptr<PixelShader>mp_ps;

	//! ラスタライザステート
	ID3D11RasterizerState *mp_ras_state;
};


#endif
