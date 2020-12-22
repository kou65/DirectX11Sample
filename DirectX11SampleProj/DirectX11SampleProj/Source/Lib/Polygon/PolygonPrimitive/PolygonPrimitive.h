#ifndef POLYGON_PRIMITIVE_H_
#define POLYGON_PRIMITIVE_H_

#include<d3d11.h>
#include<vector>
#include"../../Buffer/BufferTemplate/BufferTemplate.h"
#include"../SubSet/SubSet.h"



/**
* @brief ポリゴンの原子
*/
struct PolygonPrimitive {


	/**
	* @brief コンストラクタ
	*/
	PolygonPrimitive() : 
		tepology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
		vertex_data_size(0)
	{}


	//! 頂点バッファ
	BufferTemplate vertex_buffer;

	//! 頂点データサイズ
	UINT vertex_data_size;

	//! サブセットリスト
	std::vector<SubSet>sub_set_list;

	//! 形成方法
	D3D_PRIMITIVE_TOPOLOGY tepology;


};

#endif
