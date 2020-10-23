#ifndef POLYGON_PRIMITIVE_H_
#define POLYGON_PRIMITIVE_H_

#include<d3d11.h>
#include<Wrl.h>
#include"../../VertexBuffer/VertexBuffer.h"


//! DirectX版のスマートポインタ
using namespace Microsoft::WRL;


/**
* @class PolygonPrimitive
* @brief ポリゴンの原子
*/
class PolygonPrimitive {
public:


	/**
	* @brief コンストラクタ
	*/
	PolygonPrimitive();


	/**
	* @brief カスタムバーテックスをsizeofなどでサイズを測ったサイズ
	*/
	UINT GetCustomVertexSize();


	/**
	* @brief 頂点数を返す
	*/
	UINT GetVertexCount();


	/**
	* @brief 頂点最初
	*/
	UINT GetStartVertex();


	/**
	* @brief 形状を返す
	*/
	D3D_PRIMITIVE_TOPOLOGY GetPrimitive();


	/**
	* @brief VertexBufferを返す
	*/
	VertexBuffer GetVertexBuffer();


	/**
	* @brief インプットレイアウトのポインタを返す
	*/
	ComPtr<ID3D11InputLayout> GetPtrInputLayout();

protected:

	VertexBuffer m_vb;
	ComPtr<ID3D11InputLayout>mp_il;

	UINT m_costom_vertex_size;
	UINT m_vertex_count;
	UINT m_vertex_start;
	D3D_PRIMITIVE_TOPOLOGY m_tepology;
};

#endif
