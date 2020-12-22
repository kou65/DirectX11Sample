#ifndef OBJ_FILE_DATA_H
#define OBJ_FILE_DATA_H


#include<vector>
#include<map>
#include<DirectXMath.h>


#include"../../MaterialData/MaterialData.h"


using namespace DirectX;



/**
* @brief オブジェクトパラメータ
*/
struct OBJParam {


	/**
	* @brief コンストラクタ
	*/
	OBJParam() {

		// 変換
		pos.x = pos.y = pos.z = 0.f;
		rotation = pos;
		scale.x = scale.y = scale.z = 1.f;

		texture_name = "";
	
	}

	//! 位置
	XMFLOAT3 pos;

	//! 拡縮
	XMFLOAT3 scale;

	//! 回転値
	XMFLOAT3 rotation;

	//! カラー
	XMFLOAT4 color;

	//! obj登録名
	std::string register_obj_file_name;

	//! テクスチャ名
	std::string texture_name;

};


/**
* @brief Drawサブセット用構造体
*/
struct OBJSubset {

	OBJSubset() {
		material_index = 0;
		face_start = 0;
		face_count = 0;
	}

	//! インデックス
	unsigned int material_index;

	//! 始めの面の位置
	unsigned int face_start;

	//! 総面数
	unsigned int face_count;
};


/**
* @brief オブジェファイルで保存するデータ
*/
struct OBJFileData {

	OBJFileData() {
		material_num = 0;
	}

	//! マテリアル数
	unsigned int material_num;

	//! Objの方のマテリアル名配列
	std::vector<std::string>usemtl_name_list;

	//! 描画を入れ替えるサブセット
	std::vector<OBJSubset>object_sub_set_list;

	//! マテリアルデータ配列(マテリアル名,マテリアルデータ)
	std::map<std::string, MaterialData>material_data_list;

	//! マテリアルのテクスチャ名配列
	std::map<std::string, std::string>m_material_texture_name_list;

	//! ワールド位置
	std::vector<XMFLOAT3>world_pos_list;

	// MEMO 継承してある
	//! バーテックスバッファ
	//IDirect3DVertexBuffer9 * p_vertex_buffer;

	//! インデックスバッファ
	//IDirect3DIndexBuffer9 * p_index_buffer;
};



#endif