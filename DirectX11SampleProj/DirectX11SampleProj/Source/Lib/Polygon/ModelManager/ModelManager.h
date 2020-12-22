#ifndef MODEL_MANAGER_H_
#define MODEL_MANAGER_H_

#include<map>
#include<string>
#include"../Model/Model.h"
#include"../../MaterialData/MaterialData.h"
#include"../../Shader/ConstShader/ConstShader.h"
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../../TransformMatrixData3D/TransformMatrixData3D.h"



/**
* @brief モデル管理者クラス
*/
class ModelManager : public Singleton<ModelManager>{
public:


	friend class Singleton<ModelManager>;


	/**
	* @brief ファイルフォーマット
	*/
	enum class FileFormat {
		OBJ,
	};

public:


	// MEMO モデルの拡張子で識別しても良い
	/**
	* @brief モデルファイル読み込み
	*/
	bool Load(
		FileFormat format,
		const std::string model_file_path,
		const std::string register_name
	);


	/**
	* @brief 全て描画
	*/
	void Draw(
		const TS3DMatrixData&ts_mat_data
	);


	/**
	* @brief メッシュを部分的に描画
	*/
	void DrawSubSet(
		Model*model,
		const int&mesh_number
	);


	/**
	* @brief index_startでサブセットを行う
	*/
	void DrawIndexSubSet(
		Model*model,
		const int& mesh_number,
		const int& sub_set_number
	);


	/**
	* @brief vsシェーダーチェンジ
	* @param[in] 次に設定する頂点シェーダー
	* @param[in] 登録しているモデル名
	*/
	void ChangeVSShader(
		const ConstShader::VSType&vs_type,
		const std::string& register_name
	);


	/**
	* @brief psシェーダーチェンジ
	* @param[in] 次に設定する頂点シェーダー
	* @param[in] 登録しているモデル名
	*/
	void ChangePSShader(
		const ConstShader::PSType&ps_type,
		const std::string& register_name
	);


	/**
	* @brief 全てのモデルのvsシェーダーをチェンジ
	*/
	void AllChangeVSShader(
		const ConstShader::VSType& vs_type
	);


	/**
	* @brief 全てのモデルのpsシェーダーをチェンジ
	*/
	void AllChangePSShader(
		const ConstShader::PSType& ps_type
	);


private:


	/**
	* @brief メッシュ描画
	*/
	void DrawMesh(
		ID3D11DeviceContext*p_context,
		MeshPrimitive*mesh,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type,
		const int& index_start,
		const int& index_count,
		const int& vs_c_num = 0,
		const int& ps_c_num = 0
	);


private:


	//! モデルリスト(シェーダーごとに切り分ける)
	std::map<std::string, Model*>mp_model_list;

};

#endif
