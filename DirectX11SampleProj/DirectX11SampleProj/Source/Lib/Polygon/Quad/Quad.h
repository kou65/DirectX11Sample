#ifndef SURFACE_2D_H_
#define SURFACE_2D_H_

#include"../MeshPrimitive/MeshPrimitive.h"
#include"../../Device/Device.h"
#include"../../CustomVertex/CustomVertex2D.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../../Shader/ShaderProcess/PixelShader/PixelShader.h"



//! DirectX版のスマートポインタ
using namespace Microsoft::WRL;



/**
* @brief 平面ポリゴン
*/
class Quad{
public:


	/**
	* @brief コンストラクタ
	*/
	Quad();


	/**
	* @brief 作成
	*/
	bool Create();


	/**
	* @brief ポリゴンを返す
	*/
	PolygonPrimitive GetPolygon() {
		return m_mesh.polygon_primitive;
	}


	/**
	* @brief ポリゴンを返す
	*/
	MeshPrimitive GetMesh() {
		return m_mesh;
	}


private:

	//! 最小値
	const float MIN = 0.f;

	//! 最大値
	const float MAX = 1.f;

	//! z値
	const float Z = 0.f;

	//! 頂点バッファ数
	static const int VERTEX_COUNT = 4;

	//! インデックスリスト数
	static const int INDEX_COUNT = 6;

private:


	bool CreateStripe();


	bool CreateList();


	/**
	* @brief ポリゴン生成
	*/
	void CreateStripVertex(CustomVertexPosColor cv[VERTEX_COUNT]);


	/**
	* @brief リスト用ポリゴン生成
	*/
	void CreateListVertex(CustomVertexPosColor cv[VERTEX_COUNT]);


	/**
	* @brief リスト用インデックス生成
	*/
	void CreateListIndex(WORD index[INDEX_COUNT]);


	/**
	* @brief セットアップ射影変換
	*/
	void SetUpProj();


	/**
	* @brief セットアップワールド座標
	*/
	void SetUpWorld();


private:


	//! メッシュ原子
	MeshPrimitive m_mesh;

	//! ワールド行列
	XMMATRIX m_world;

	//! 射影行列
	XMMATRIX m_proj;


};


#endif
