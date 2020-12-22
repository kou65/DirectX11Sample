#ifndef OBJ_FILE_H
#define OBJ_FILE_H

#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>
#include<DirectXMath.h>
#include"../../CustomVertex/CustomVertexPosNorCol.h"
#include"../ObjFileData/ObjFileData.h"
#include"../../Polygon/Model/Model.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"



using namespace DirectX;



/*
位置や回転、拡縮情報などは始めに計算して、行列化しておき、
描画で値をセットできるようにしておく
*/


/**
* @brief objファイルシングルトンクラス
*/
class OBJFile{
public:


	/**
	* @brief シングルトン
	* @return static Obj * オブジェポインタ
	*/
	static OBJFile *GetInstance(){
		static OBJFile obj_file;
		return &obj_file;
	}


public:


	/**
	* @brief 初期化
	* @return bool 初期化が成功したらtrueを返す
	*/
	bool Init();


	/**
	* @brief モデル読み込み
	* @param[in] obj_file_path 読み込むobjファイル名
	* @param[in] registr_name 登録obj名
	* @param[in] mtl_file_path objマテリアルファイル名
	* @return bool 読み込めたかどうかを返す
	*/
	bool LoadModel(
		const std::string &obj_file_path,
		const std::string &registr_name,
		Model& model,
		const std::string &mtl_file_path = ""
	);


	/**
	* @brief オブジェファイルにモデル読み込み
	*/
	bool Load(
		const std::string& obj_file_path,
		const std::string& registr_name,
		const std::string& mtl_file_path = ""
	);
	

	/**
	* @brief インスタンシング描画の位置セット
	*/
	void InstancingSet(
		const std::string&register_obj_file_name,
		const XMFLOAT3&pos
	);


	/**
	* @brief 解放処理
	*/
	void ReleaseResource();


private:


	/**
	* @brief コンストラクタ
	*/
	OBJFile();


	/**
	* @brief メッシュ情報読み込み
	* @param[in] file_path objファイル名
	* @param[in] registr_name obj登録名
	* @param[out] out_material_name マテリアル名を外部に参照
	* @param[out] out_total_material_num 外部にマテリアル数を参照
	* @param[out] indices インデックスリスト
	* @param[out] mesh_list メッシュカスタムバーテックスリスト
	*/
	bool MeshLoad(
		const std::string &file_path,
		const std::string &registr_name,
		std::string&out_material_name,
		int &out_total_material_num,
		std::vector<int>&indices,
		std::vector<CustomVertexPosNorCol>&mesh_list
	);


	/**
	* @brief 面情報からカスタムバーテックス作成
	* @param[out] p_file ファイルポインタ
	* @param[in] register_name 外部からきた登録名
	* @param[out] indices インデックスリスト
	* @param[out] mesh_list メッシュリスト
	* @param[out] vertex_list 頂点リスト
	* @param[out] uv_list uvリスト
	* @param[out] normal_list 法線リスト
	*/
	void FaceInfoLoad(
		FILE*p_file,
		const std::string &register_name,
		std::vector<int>&indices,
		std::vector<CustomVertexPosNorCol>&mesh_list,
		const std::vector<XMFLOAT3>&vertex_list,
		const std::vector<XMFLOAT2>&uv_list,
		const std::vector<XMFLOAT3>&normal_list
	);


	/**
	* @brief 頂点情報読み込み
	* @param[out] p_file ファイルポインタ
	* @param[in] front_str 最初の文字列
	* @param[out] out_vertex_list 頂点リスト
	* @param[out] out_uv_list uvリスト
	* @param[out] out_normal_list 法線リスト
	*/
	void VertexInfoLoad(
		FILE *p_file,
		const char*front_str,
		std::vector<XMFLOAT3>&out_vertex_list,
		std::vector<XMFLOAT2>&out_uv_list,
		std::vector<XMFLOAT3>&out_normal_list
	);


	/**
	* @brief マテリアルファイル読み込み
	* @param[in] mtl_file_name マテリアルファイル名
	* @param[in] obj_file_name objファイル名
	* @param[in] texture_file_path テクスチャファイルパス名
	*/
	bool MaterialFileLoad(
		const std::string &mtl_file_name,
		const std::string &obj_file_name,
		const std::string &texture_file_path
	);


	// usemtl読み込み
	/**
	* @brief usemtl読み込み
	* @param[out] p_file ファイルポインタ
	* @param[in] obj_file_name objファイル名
	* @param[in] out_total_material_num 総マテリアル数
	* @param[in] indices インデックスリスト
	* @param[in] front_str 前方文字列
	* @param[in] load_buffer 読み込みバッファ
	*/
	void LoadUseMaterialInfo(
		FILE*p_file,
		const std::string &obj_file_name,
		int &out_total_material_num,
		std::vector<int>&indices,
		char*front_str,
		int load_buffer
	);


	/**
	* @brief 面情報代入
	* @param[in] face_info_str 面情報文字列
	* @param[out] custom_vertex カスタムバーテックス
	* @param[out] m_indices インデックスリスト 
	* @param[in] vertex_list 頂点リスト
	* @param[in] uv_list uvリスト
	* @param[in] normal_list 法線リスト
	* @param[out] out_draw_sub_set サブセット構造体
	*/
	void InsertFaceList(
		const std::vector<std::vector<std::string>>&face_info_str,
		std::vector<CustomVertexPosNorCol>&custom_vertex,
		std::vector<int>&m_indices,
		const std::vector<XMFLOAT3>&vertex_list,
		const std::vector<XMFLOAT2>&uv_list,
		const std::vector<XMFLOAT3>&normal_list,
		std::vector<OBJSubset>&out_draw_sub_set
	);


	/**
	* @brief 整数値変換
	* @param[out] axis 軸数
	* @param[in] string 文字列を元に頂点算出
	*/
	bool Vector3ConversionByString(
		int &axis,
		const std::string &string
	);


	/**
	* @brief 4面を3面にする
	* @param[in] vertex4_polygon_list 頂点4リスト
	* @return std::vector<INT> 分割済みのリスト
	*/
	std::vector<INT> Vertex4CutToVertex3Face(
		const std::vector<INT>&vertex4_polygon_list
	);


	/**
	* @brief 頂点ファイル読み込み
	* @param[in] p_file ファイルポインタ
	* @param[in] vec3 ファイルから読み込んだ頂点数
	*/
	void VertexFscanfLoad(
		FILE*p_file,
		XMFLOAT3 &vec3
	);


	/**
	* @brief 変換行列を返す
	* @param[in] param objパラメータ
	* @return D3DXMATRIX 変換後の行列
	*/
	XMMATRIX GetTransformMatrix(const OBJParam&param);


	/**
	* @brief モデル化する
	*/
	bool CreateModel(
		Model&model,
		const int& vertex_num,
		const int& face_num,
		const std::string& register_name,
		const std::vector<CustomVertexPosNorCol>& mesh_vertex_list,
		const std::vector<int>& indices
	);


private:


	//! オブジェファイルリスト
	std::map<std::string, Model>m_model_list;

	//! オブジェファイルデータリスト
	std::map<std::string, OBJFileData*>m_obj_file_data_list;


};

#endif