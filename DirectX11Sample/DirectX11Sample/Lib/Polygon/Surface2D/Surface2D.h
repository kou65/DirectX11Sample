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
* @class Surface2D
* @brief 平面ポリゴン
*/
class Surface2D : public MeshPrimitive{
public:


	/**
	* @brief コンストラクタ
	*/
	Surface2D();


	/**
	* @brief 作成
	*/
	bool Create(Device* dev,VertexShader*vb);

private:

	//! 最小値
	const float MIN = -0.5f;

	//! 最大値
	const float MAX = 0.5f;

	//! z値
	const float Z = 0.f;

	//! 頂点バッファ数
	static const int VERTEX_COUNT = 4;

	//! インデックスリスト数
	static const int INDEX_COUNT = 6;

private:


	/**
	* @brief ポリゴン生成
	*/
	void CreatePolygon(CustomVertexPosColor cv[VERTEX_COUNT]);


	/**
	* @brief インデックスリスト作成
	*/
	void CreateIndexList(WORD list[INDEX_COUNT]);

};


#endif
