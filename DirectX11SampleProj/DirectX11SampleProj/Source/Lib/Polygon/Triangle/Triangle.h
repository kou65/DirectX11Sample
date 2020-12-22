#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include"../PolygonPrimitive/PolygonPrimitive.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../../CustomVertex/CustomVertex2D.h"



/**
* @brief Traiangle形状
*/
class Triangle{
public:


	/**
	* @brief コンストラクタ
	*/
	Triangle();


	/**
	* @brief ポリゴン作成
	*/
	bool Create(ID3D11Device* device);


	/**
	* @brief ポリゴン取得
	*/
	PolygonPrimitive GetPolygon() {
		return m_polygon;
	}

private:


	/**
	* @brief バーテックスをセットアップ 
	*/
	void SetUpTriangleVertex(CustomVertexPosColor cv[3]);


private:

	//! ポリゴン原子
	PolygonPrimitive m_polygon;

};

#endif
