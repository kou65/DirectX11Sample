#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include"../../Math/Math.h"
#include"../../IOFunction/IOFunction.h"
#include"../OBJFile/ObjFile.h"
#include"../../MaterialData/MaterialData.h"
#include"../../Polygon/Model/Model.h"



OBJFile::OBJFile(){

}


bool OBJFile::Init() {

	return true;
}


void OBJFile::ReleaseResource() {

	for (auto &i : m_obj_file_data_list) {
		// 解放
		//i.second->p_index_buffer->Release();
		//i.second->p_vertex_buffer->Release();

		i.second->object_sub_set_list.clear();
		i.second->world_pos_list.clear();
		i.second->usemtl_name_list.clear();
		i.second->material_data_list.clear();
	}

	m_obj_file_data_list.clear();
}


void OBJFile::InstancingSet(
	const std::string&register_obj_file_name,
	const XMFLOAT3&pos
) {

	m_obj_file_data_list[register_obj_file_name]->world_pos_list.emplace_back(pos);
}


XMMATRIX OBJFile::GetTransformMatrix(const OBJParam&param) {
	

	// ワールド座標初期化
	XMMATRIX total_mat, rota_mat, scale_mat, move_mat;

	total_mat =
		XMMatrixIdentity();

	XMMATRIX rota_x, rota_y, rota_z;

	rota_x =
		XMMatrixIdentity();
	rota_y =
		XMMatrixIdentity();
	rota_z =
		XMMatrixIdentity();


	// 回転
	XMMatrixRotationZ(Math::DegreesToRad(param.rotation.z));
	XMMatrixRotationX(Math::DegreesToRad(param.rotation.x));
	XMMatrixRotationY(Math::DegreesToRad(param.rotation.y));

	// 回転行列作成
	rota_mat = (rota_z * rota_y * rota_x);

	// 拡縮
	scale_mat = XMMatrixScaling(param.scale.x, param.scale.y, param.scale.z);

	// 移動
	move_mat = XMMatrixTranslation(param.pos.x, param.pos.y, param.pos.z);

	total_mat = (scale_mat * rota_mat * move_mat);

	return total_mat;
}


bool OBJFile::Load(
	const std::string&obj_file_path,
	const std::string&register_name,
	const std::string&mtl_file_path
) {

	// モデル読み込み
	if (LoadModel(
		obj_file_path,
		register_name,
		m_model_list[register_name],
		mtl_file_path
	) == false) {
		return false;
	}

	return true;
}


bool OBJFile::LoadModel(
	const std::string&obj_file_path,
	const std::string&register_name,
	Model&model,
	const std::string&mtl_file_path) {


	std::vector<std::string>split_file_name;

	// サイズがないならobjファイルがある階層ディレクトリを取ってくる
	if (mtl_file_path.size() <= 0) {
		split_file_name = 
			Utility::IOFunction::SplitStr('/', obj_file_path);
	}
	else {
		split_file_name.emplace_back(mtl_file_path);
		split_file_name.emplace_back();
	}

	// マテリアルデータバッファ
	std::vector<MaterialData>material_data_list;

	// マテリアル名
	std::string material_name;

	// 頂点バッファ
	std::vector<CustomVertexPosNorCol>mesh_vertex_list;

	// 面情報バッファ
	std::vector<int>indices;

	// 総マテリアル数
	int material_num = 0;


	// メイン読み込み
	if (MeshLoad(
		obj_file_path,
		register_name,
		material_name,
		material_num,
		indices,
		mesh_vertex_list) == false) {
		return false;
	}

	std::string file_path_material_name;
	std::string file_path_texture;

	// 最後のカレントdは外す
	for (unsigned int i = 0; i < split_file_name.size() - 1; i++) {
		 file_path_material_name += split_file_name[i];
	}

	// テクスチャファイルパス作成
	file_path_texture = file_path_material_name;

	// ファイルパス付のマテリアル名にする
	file_path_material_name += material_name;

	// マテリアル読み込み
	MaterialFileLoad(
		file_path_material_name,
		register_name,
		file_path_texture
	);

	// 総マテリアル数保存
	m_obj_file_data_list[register_name]->material_num = material_num;

	// モデル作成
	CreateModel(
		model,
		(int)mesh_vertex_list.size(),
		(int)indices.size(),
		register_name,
		mesh_vertex_list,
		indices
	);

	return true;
}



bool OBJFile::MeshLoad(
	const std::string &file_path,
	const std::string &registr_name,
	std::string&out_material_name,
	int &out_total_material_num,
	std::vector<int>&indices,
	std::vector<CustomVertexPosNorCol>&mesh_list
	) {

	// 頂点読み込みバッファ
	std::vector<XMFLOAT3>vertex_list;

	// 法線読み込みバッファ
	std::vector<XMFLOAT3>normal_list;

	// テクスチャ座標バッファ
	std::vector<XMFLOAT2>uv_list;

	// ファイルストリーム
	FILE *p_file = nullptr;

	HRESULT result;

	std::string obj_file_path = file_path;

	// ファイルオープン
	result = fopen_s(&p_file, obj_file_path.c_str(), "r");

	// これをしないと警告
	if (p_file == nullptr) {
		return false;
	}

	// オブジェクトファイルデータを生成
	m_obj_file_data_list[registr_name] = new OBJFileData;

	// とりあえず256で
	const int BUFFER = 256;

	// 前方文字列
	char front_str[BUFFER];

	// 分割用の文字列配列
	std::vector<std::string>split_str;
	

	while (feof(p_file) == 0) {

		// 初期化
		front_str[0] = '\0';

		// 先頭の情報を取得する
		fscanf_s(p_file, "%s ", (char*)front_str, BUFFER);

		// 先頭文字列がコメントならはじく
		if (front_str[0] == '#') {
			continue;
		}
		
		// 頂点関係なら
		else if (front_str[0] == 'v') {

			// 頂点関係読み込み
			VertexInfoLoad(
				p_file,
				front_str,
				vertex_list,
				uv_list,
				normal_list
			);
		}
		
		// 面情報なら
		else if (front_str[0] == 'f' && front_str[1] == '\0') {

			// 面情報読み込み
			FaceInfoLoad(
				p_file,
				registr_name,
				indices,
				mesh_list,
				vertex_list,
				uv_list,
				normal_list
			);
		}
		// マテリアルファイル名読み込み
		else if (strcmp(front_str,"mtllib") == 0) {
		
			fscanf_s(p_file, "%s",&front_str,BUFFER);
			out_material_name = front_str;
		}
		// 使用するマテリアル情報なら要素加算
		else if (strcmp(front_str, "usemtl") == 0) {

			// 使用マテリアル読み込み
			LoadUseMaterialInfo(
				p_file,
				registr_name,
				out_total_material_num,
				indices,
				front_str,
				BUFFER
			);
		}
	}
	

	// ファイルを閉じる
	fclose(p_file);

	return true;
}


void OBJFile::VertexFscanfLoad(
	FILE*p_file,
	XMFLOAT3 &vec3) {

	// x軸,y軸,z軸を取得
	fscanf_s(
		p_file, "%f %f %f",
		&vec3.x,
		&vec3.y,
		&vec3.z);
}


void OBJFile::VertexInfoLoad(
	FILE *p_file,
	const char*front_str,
	std::vector<XMFLOAT3>&out_vertex_list,
	std::vector<XMFLOAT2>&out_uv_list,
	std::vector<XMFLOAT3>&out_normal_list
) {

	XMFLOAT3 vec3;

	// x軸,y軸,z軸を読み込み
	VertexFscanfLoad(p_file, vec3);

	// 頂点なら
	if (front_str[1] == '\0') {

		// *-1.fで左手系に変換できる
		vec3.x *= -1.f;

		out_vertex_list.push_back(vec3);
	}
	// 法線なら
	else if (front_str[1] == 'n') {

		// 反転
		vec3.x *= -1.f;

		out_normal_list.push_back(vec3);
	}
	// テクスチャ座標なら
	else if (front_str[1] == 't') {

		// uvのみy軸で反転
		vec3.y *= -1.f;

		// vec3をvec2にする
		XMFLOAT2 vec2(vec3.x,vec3.y);

		out_uv_list.push_back(vec2);
	}
}


void OBJFile::FaceInfoLoad(
	FILE*p_file,
	const std::string &register_name,
	std::vector<int>&indices,
	std::vector<CustomVertexPosNorCol>&mesh_list,
	const std::vector<XMFLOAT3>&vertex_list,
	const std::vector<XMFLOAT2>&uv_list,
	const std::vector<XMFLOAT3>&normal_list
) {

	// とりあえず256 * 8バイト
	const int LOAD_BUFFER = 256;

	// 読み込み文字列バッファ
	char load_str[LOAD_BUFFER] = {};

	// 空白分割文字列バッファ
	std::vector<std::string>space_split_str;

	// 文字列面情報バッファ
	std::vector<std::vector<std::string>>face_info_str;

	// ファイル読み込み
	fgets(
		load_str,
		LOAD_BUFFER,
		p_file
	);

	// 要素追加
	space_split_str.emplace_back();

	// 空白で文字列分割
	space_split_str = Utility::IOFunction::SplitStr(' ', load_str);

	int face_num = 0;

	for (auto &str : space_split_str) {

		// 面情報文字列
		face_info_str.emplace_back();

		// 面情報文字列
		face_info_str[face_num].emplace_back();

		// /で文字列分割
		face_info_str[face_num] = 
			Utility::IOFunction::SplitStr('/', str);

		// 面数加算
		face_num++;
	}

	// 仮の入れ物
	std::vector<int>prov_face;

	// 面情報を代入
	InsertFaceList(
		face_info_str,
		mesh_list,
		indices,
		vertex_list,
		uv_list,
		normal_list,
		m_obj_file_data_list[register_name]->object_sub_set_list
	);

}


void OBJFile::InsertFaceList(
	const std::vector<std::vector<std::string>>&face_info_str,
	std::vector<CustomVertexPosNorCol>&custom_vertex,
	std::vector<int>&indices,
	const std::vector<XMFLOAT3>&vertex_list,
	const std::vector<XMFLOAT2>&uv_list,
	const std::vector<XMFLOAT3>&normal_list,
	std::vector<OBJSubset>&out_draw_sub_set
) {


	/**
	* @enum VertexType 頂点の種類
	*/
	enum class VertexType {
		VERTEX,
		UV,
		NORMAL,
		TOTAL_VERTEX_TYPE,
	};

	// 読み取れない場合
	const int NONE = -1;
	
	// 頂点番号用(-1は情報を受け取れなかった初期状態)
	int vertex_info[3] = 
	{
		NONE,NONE,NONE,
	};

	int subject_vertex = 0;

	std::vector<int>prov_face;

	// 面情報文字列
	for (size_t i = 0;
		i < face_info_str.size();
		i++) {

	
		// 頂点データ
		CustomVertexPosNorCol vertex_data;

		// 法線がない場合
		if (face_info_str[i].size() <= 2) {
			subject_vertex = 3 - 
				static_cast<int>(face_info_str[i].size());
		}

		// 軸分回す
		for (int j = 0; j < 3 - subject_vertex; j++) {


			// 頂点情報に変換する
			Vector3ConversionByString(vertex_info[j],face_info_str[i][j]);

			int id = 0;

			if (vertex_info[j] != 0) {
				id = vertex_info[j] - 1;
			}

			// 面情報へ代入
			switch (j) {

			case (int)VertexType::VERTEX:
				vertex_data.pos[0] = vertex_list[id].x;
				vertex_data.pos[1] = vertex_list[id].y;
				vertex_data.pos[2] = vertex_list[id].z;
				break;

			case (int)VertexType::UV:

				if (uv_list.size() > 0) {
					//vertex_data.uv = uv_list[id];
				}
				break;

			case (int)VertexType::NORMAL:

				if (normal_list.size() > 0) {
					vertex_data.normal[0] = normal_list[id].x;
					vertex_data.normal[1] = normal_list[id].y;
					vertex_data.normal[2] = normal_list[id].z;
				}
				break;
			}
		}

		custom_vertex.push_back(vertex_data);
		
		prov_face.push_back(
			static_cast<int>(
				custom_vertex.size() - 1
				)
		);
		
	}

	// 頂点数が4以上なら
	if (face_info_str.size() >= 4) {

		// 面を切り分ける
		prov_face = 
			Vertex4CutToVertex3Face(prov_face);

		for (size_t i = 0;
			i < prov_face.size();
			i++
			) {

			// 現在のサブセットリストの面数を加算
			out_draw_sub_set.back().face_count++;

			// インデックスに追加
			indices.push_back(prov_face[i]);

			if (i == 2 || i == 5) {
				// ポリゴンの作成の頂点順番を反転する
				int size = static_cast<int>(indices.size());

				int curr = size - 1;
				int prev = size - 3;

				int temp = static_cast<int>(indices[curr]);
				indices[curr] = indices[prev];
				indices[prev] = temp;
			}
		}
	}
	// 3頂点なら
	else {

		for (size_t i = 0; i < prov_face.size(); i++) {

			// 現在のサブセットリストの面数を加算
			out_draw_sub_set.back().face_count++;

			indices.push_back(prov_face[i]);
		}

		// ポリゴンの作成の頂点順番を反転する
		int size = static_cast<int>(indices.size());

		int curr_size = size - 1;
		int prev_size = size - 3;

		int temp = indices[curr_size];
		indices[curr_size] = indices[prev_size];
		indices[prev_size] = temp;
	}
}


bool OBJFile::MaterialFileLoad(
	const std::string &mtl_file_name,
	const std::string &register_name,
	const std::string &file_path_texture
) {

	const int BUFFER = 256;

	char load_str[BUFFER];

	// 文字列分割用
	std::vector<std::string>str_list;

	// テクスチャ文字列読み取り用
	std::string texture_str;

	// カラーの最大値
	const int COLOR_NUM = 3;

	// カラー情報を保存する
	float color_info[COLOR_NUM] = {};

	// 特定のオブジェクトファイルデータを受け取る
	OBJFileData*p_obj_file_data = m_obj_file_data_list[register_name];

	// マテリアルファイル名
	std::ifstream ifs(mtl_file_name);

	// ファイル読み込みに失敗した場合
	if (ifs.fail() == true) {
		return false;
	}

	// ファイル読み込み
	while (ifs.getline(load_str, BUFFER - 1))
	{

		// 文字列分割
		str_list = 
			Utility::IOFunction::SplitStr(' ', load_str);

		// 新しいマテリアル
		if (strcmp(str_list[0].c_str(),"newmtl ") == 0) {

			// テクスチャ名受け取り
			m_obj_file_data_list[register_name]->
				m_material_texture_name_list[str_list[1].c_str()] = str_list[1].c_str();

			texture_str = str_list[1].c_str();

			// 使わない色を初期化
			XMFLOAT4 color = {
				0.f,
				0.f,
				0.f,
				1.0f
			};


			p_obj_file_data->material_data_list[texture_str].emissive.x = color.x;
			p_obj_file_data->material_data_list[texture_str].emissive.y = color.y;
			p_obj_file_data->material_data_list[texture_str].emissive.z = color.z;
			p_obj_file_data->material_data_list[texture_str].emissive.w = color.w;

		}
		// アンビエントカラー
		else if (strcmp(str_list[0].c_str(), "Ka ") == 0) {

			XMFLOAT4 color = {
				static_cast<float>(atof(str_list[1].c_str())),
				static_cast<float>(atof(str_list[2].c_str())),
				static_cast<float>(atof(str_list[3].c_str())),
				1.0f
			};

			// マテリアルに代入
			p_obj_file_data->material_data_list[texture_str].ambient.x = color.x;
			p_obj_file_data->material_data_list[texture_str].ambient.y = color.y;
			p_obj_file_data->material_data_list[texture_str].ambient.z = color.z;
			p_obj_file_data->material_data_list[texture_str].ambient.w = color.w;

		}
		// ディフューズカラー
		else if (strcmp(str_list[0].c_str(), "Kd ") == 0) {

			XMFLOAT4 color = {
				static_cast<float>(atof(str_list[1].c_str())),
				static_cast<float>(atof(str_list[2].c_str())),
				static_cast<float>(atof(str_list[3].c_str())),
				1.0f
			};

			// マテリアルに代入
			p_obj_file_data->material_data_list[texture_str].diffuse.x = color.x;
			p_obj_file_data->material_data_list[texture_str].diffuse.y = color.y;
			p_obj_file_data->material_data_list[texture_str].diffuse.z = color.z;
			p_obj_file_data->material_data_list[texture_str].diffuse.w = color.w;

		}
		// スペキュラーカラー
		else if (strcmp(str_list[0].c_str(), "Ks ") == 0) {

			XMFLOAT4 color = {
				static_cast<float>(atof(str_list[1].c_str())),
				static_cast<float>(atof(str_list[2].c_str())),
				static_cast<float>(atof(str_list[3].c_str())),
				1.0f
			};

			// マテリアルに代入
			p_obj_file_data->material_data_list[texture_str].specular.x = color.x;
			p_obj_file_data->material_data_list[texture_str].specular.y = color.y;
			p_obj_file_data->material_data_list[texture_str].specular.z = color.z;
			p_obj_file_data->material_data_list[texture_str].specular.w = color.w;
		}
		// α値なら
		else if (strcmp(str_list[0].c_str(), "d ") == 0) {

			// α値設定
			p_obj_file_data->material_data_list[texture_str].ambient.w = 
				static_cast<float>(atof(str_list[1].c_str()));

			p_obj_file_data->material_data_list[texture_str].diffuse.w = 
				static_cast<float>(atof(str_list[1].c_str()));

			p_obj_file_data->material_data_list[texture_str].specular.w = 
				static_cast<float>(atof(str_list[1].c_str()));

		}

		// パワー
		else if (strcmp(str_list[0].c_str(), "Ns ") == 0) {

			//m_obj_file_data_list[register_name]->
			//	material_data_list[texture_str].
			//	material.Power = 
			//	static_cast<float>(atof(str_list[1].c_str()));
		}
		// テクスチャなら
		else if (strcmp(str_list[0].c_str(), "map_Kd ") == 0) {

			// テクスチャ名がないなら
			if (str_list[1].empty() == true) {
				continue;
			}

			std::string texture_name = 
				file_path_texture + str_list[1];

			// テクスチャ名代入
			p_obj_file_data->m_material_texture_name_list[texture_str] = texture_str;

			//// テクスチャ読み込み
			//TextureManager::GetInstance()->Load(
			//	texture_name.c_str(),
			//	p_obj_file_data->material_data_list[texture_str].
			//	texture_name.c_str()
			//);
		}
	}

	return true;
}


void OBJFile::LoadUseMaterialInfo(
	FILE*p_file,
	const std::string &register_name,
	int &out_total_material_num,
	std::vector<int>&indices,
	char*front_str,
	int load_buffer
) {

	// 特定のオブジェクトファイルデータを受け取る
	OBJFileData*p_obj_file_data = 
		m_obj_file_data_list[register_name];

	// マテリアル
	{
		// マテリアル数加算
		out_total_material_num++;

		// ファイル読み込み
		fscanf_s(p_file, "%s", front_str, load_buffer);

		// 面情報数受け取り
		p_obj_file_data->usemtl_name_list.push_back(front_str);
	}

	// DrawSubSet
	{
		// 要素追加
		p_obj_file_data->object_sub_set_list.emplace_back();

		// マテリアル数加算
		p_obj_file_data->object_sub_set_list.back().material_index =
			out_total_material_num;

		// 最初から加算していく
		p_obj_file_data->object_sub_set_list.back().face_count =
			0;

		// 最初の面を入れる
		p_obj_file_data->object_sub_set_list.back().face_start =
			static_cast<int>(indices.size());
	}

}


bool OBJFile::Vector3ConversionByString(
	int &axis,
	const std::string &string
) {

	if (string.empty() == true) {
		//Window::TextMessageBox("文字列分割に失敗しました");
		return false;
	}

	// スラッシュなら
	if (string == "/") {
		return false;
	}
	else {
		// 小数点変換
		axis = atoi(string.c_str());
	}

	return true;
}


std::vector<INT> OBJFile::Vertex4CutToVertex3Face(
	const std::vector<INT>&vertex4_polygon_list
) {

	// 4面の場合は3面にする

	// 面情報受け取り用
	std::vector<INT>get_face_list;

	// 2ポリゴン用意
	const int POLYGON2 = 2;

	// 代入する頂点(4つ分)
	const int ENTRY_VERTEX_NUM[6] = 
	{
		// 1面
		0,1,3,
		// 2面
		3,1,2 
	};

	// 頂点分回す
	for (int j = 0; j < (3 * 2); j++) {

		// 配列要素追加
		get_face_list.emplace_back();

		// 3頂点追加
		get_face_list[j] =
			vertex4_polygon_list[ENTRY_VERTEX_NUM[j]];
	}

	return get_face_list;
}


bool OBJFile::CreateModel(
	Model&model,
	const int& vertex_num,
	const int& face_num,
	const std::string& register_name,
	const std::vector<CustomVertexPosNorCol>& vertex_list,
	const std::vector<int>& indices
) {

	// 特定のオブジェクトファイルデータを受け取る
	OBJFileData* p_obj_file_data = m_obj_file_data_list[register_name];

	// デバイス
	ID3D11Device* p_dev = Device::GetInstance()->GetPtrDevice();

	// ポリゴン
	PolygonPrimitive polygon;

	// ポリゴンの設定
	{
		// 形成方法
		polygon.tepology = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		SubSet v_subset;

		v_subset.count = vertex_num;
		v_subset.start = 0;

		polygon.sub_set_list.emplace_back(v_subset);

		polygon.vertex_data_size = 
			sizeof(CustomVertexPosNorCol);

		// 頂点バッファの作成
		{
			D3D11_BUFFER_DESC v_desc;

			// 頂点バッファの初期化設定
			v_desc.ByteWidth = static_cast<UINT>((sizeof(CustomVertexPosNorCol) * vertex_list.size()));
			v_desc.Usage = D3D11_USAGE_DEFAULT;
			v_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
			v_desc.CPUAccessFlags = 0;
			v_desc.MiscFlags = 0;
			v_desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA v_data;
			// 初期化時に設定するバッファデータ
			v_data.pSysMem = &vertex_list[0]; // 先頭アドレス
			v_data.SysMemPitch = 0;
			v_data.SysMemSlicePitch = 0;

			// バーテックスバッファ作成
			polygon.vertex_buffer.Init(
				p_dev,
				v_desc,
				v_data
			);
		}
	}


	// メッシュ
	MeshPrimitive mesh;
	// ポリゴンをセット
	mesh.polygon_primitive = polygon;
	// 32ビット
	mesh.format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;


	// インデックスバッファの作成
	{

		D3D11_BUFFER_DESC i_desc;

		// 頂点バッファの初期化設定
		i_desc.ByteWidth = static_cast<UINT>((sizeof(int) * indices.size()));
		i_desc.Usage = D3D11_USAGE_DEFAULT;
		i_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		i_desc.CPUAccessFlags = 0;
		i_desc.MiscFlags = 0;
		i_desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA i_data;
		// 初期化時に設定するバッファデータ
		i_data.pSysMem = &indices[0]; // 先頭アドレス
		i_data.SysMemPitch = 0;
		i_data.SysMemSlicePitch = 0;

		// インデックスバッファ
		mesh.index_buffer.Init(
			p_dev,// デバイス
			i_desc,
			i_data
		);
	}
	
	// 使用マテリアル数からマテリアルをセットさせる
	for (UINT i = 0; i < 
		p_obj_file_data->usemtl_name_list.size();
		++i) {

		std::string str = 
			p_obj_file_data->usemtl_name_list[i];

		MaterialData data = 
			p_obj_file_data->material_data_list[str];

		// マテリアルデータを代入
		mesh.material_data_list.emplace_back(data);

	}

	// サブセットの設定
	SubSet subset;

	for (auto obj_subset : p_obj_file_data->object_sub_set_list) {

		// インデックススタート(インデックスバッファのどこから開始するか)
		subset.start =
			obj_subset.face_start;

		// インデックス数(面数)
		subset.count =
			obj_subset.face_count;

		// 追加
		mesh.sub_set_list.emplace_back(subset);
	}

	// メッシュをセット
	model.AddMesh(mesh);

	return true;
}


/*
void OBJFile::DrawBeginPassShader(
	ShaderBase* p_shader,
	OBJFileData* p_data,
	const OBJParam& param,
	const UINT& current_pass,
	int sub_num
) {

	// テクスチャが存在するかどうか
	bool is_texture = false;

	// 使用マテリアル名取得
	std::string usemtl_name = 
		p_data->usemtl_name_list[sub_num];

	// マテリアル情報取得
	MaterialInfo mtl =
		p_data->
		material_data_list[usemtl_name];

	// 代入用
	std::string texture_name =
		param.texture_name;


	// 3D描画に必要なパラメータをセット
	Model::Set3DParameter(
		Graphics::GetInstance(),
		p_data->p_index_buffer,
		p_data->p_vertex_buffer,
		sizeof(MeshCustomVertex),
		// マテリアル
		mtl.material,
		FVF_CUSTOM
	);

	// 情報受け取り
	UINT face_start = p_data->
		object_sub_set_list[sub_num].face_start;
	// 面数
	UINT face_count = p_data->
		object_sub_set_list[sub_num].face_count;

	// パスの開始
	p_shader->BeginPass(current_pass);

	// インデックス描画
	mp_graphics->GetDevice()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		// 頂点インデックスオフセット値
		0,
		// 描画に使用する最小のインデックス番号を指定(多少無駄にしていいなら0)
		face_start,
		// 上引数の最小以降の頂点数を指定
		face_count * 3,
		// 描画を開始する頂点インデックスまでのオフセット値を指定
		face_start,
		// 上のSTART_INDEX引数を先頭として描画するポリゴンの数を指定する(ポリゴンの数,頂点の数ではない)
		face_count
	);

	p_shader->EndPass();
}
*/