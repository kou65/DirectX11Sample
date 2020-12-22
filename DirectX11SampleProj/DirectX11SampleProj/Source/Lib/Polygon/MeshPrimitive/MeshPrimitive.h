#ifndef MESH_PRIMITIVE_H_
#define MESH_PRIMITIVE_H_



#include<vector>
#include"../PolygonPrimitive/PolygonPrimitive.h"
#include"../../Buffer/BufferTemplate/BufferTemplate.h"
#include"../SubSet/SubSet.h"
#include"../../MaterialData/MaterialData.h"



/**
* @brief メッシュを作る為の継承クラス
*/
class MeshPrimitive{
public:


	/**
	* @brief コンストラクタ
	*/
	MeshPrimitive() :
		format(DXGI_FORMAT_R16_UINT)
	{};


	//! ポリゴン原子
	PolygonPrimitive polygon_primitive;

	//! メッシュの中でサブセットを分ける為のパラメータ
	std::vector<SubSet>sub_set_list;
	
	//! 16ビットか32ビットかでインデックスバッファを作成する
	DXGI_FORMAT format;

	//! インデックスバッファ
	BufferTemplate index_buffer;

	//! マテリアルデータ
	std::vector<MaterialData>material_data_list;
};

#endif
