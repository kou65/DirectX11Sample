#ifndef PRIMITIVE_RENDERER_H_
#define PRIMITIVE_RENDERER_H_


#include<memory>
#include<DirectXMath.h>
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../Polygon/MeshPrimitive/MeshPrimitive.h"
#include"../Shader/ConstShader/ConstShader.h"



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
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type
	);


	/**
	* @brief デバイスの情報を使ったポリゴン描画
	*/
	void RenderingPolygonByDeviceView(
		PolygonPrimitive* pol,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type
	);


	/**
	* @brief デバイスの情報を使ったメッシュ描画
	*/
	void RenderingMesh(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		MeshPrimitive* mesh,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type,
		const int& vs_c_num,
		const int& ps_c_num
	);


	/**
	* @brief デバイスの情報を使ったメッシュ描画
	*/
	void RenderingMeshByDeviceView(
		MeshPrimitive* mesh,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type,
		const int& vs_c_num = 0,
		const int& ps_c_num = 0
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


	/**
	* @brief 定数バッファセット
	*/
	void VSSetConstBuffer(
		ConstShader::VSType vs_type,
		int slot_num
	);


	/**
	* @brief 定バッファセット
	*/
	void PSSetConstBuffer(
		ConstShader::PSType ps_type,
		int slot_num
	);


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
