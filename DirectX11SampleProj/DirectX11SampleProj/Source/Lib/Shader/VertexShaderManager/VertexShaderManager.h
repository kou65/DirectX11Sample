#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include<map>
#include<vector>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/VertexShader/VertexShader.h"
#include"../Factory/VSFactoryBase/VSFactoryBase.h"
#include"../InputDescInfo/InputDescInfo.h"




// MEMO シェーダーを分けて管理しなくても 

// VertexShaderManager::GetInstance()->Create(
//   VERTEX                                  // シェーダーの種類
// 	 "CSO/VertexShader.cso",                 // 指定CSOファイルの読み込み(それがどのhlslファイルか確認して読み込む)
// 	 ConstShader::VSType::NORMAL          // 識別番号(文字列にするか)
// );

/**
* @class VertexShaderManager
* @brief 頂点シェーダーを管理するクラス
*/
class VertexShaderManager : public Singleton<VertexShaderManager> {
public:


	/**
	* @brief フレンド
	*/
	friend class Singleton<VertexShaderManager>;


	/**
	* @brief コンストラクタ
	*/
	VertexShaderManager();


	/**
	* @brief デストラクタ
	*/
	~VertexShaderManager();


	/**
	* @brief シェーダファイル生成
	*/
	bool Create(
		const std::string&cso_file_name,
		const ConstShader::VSType&register_type,
		const ConstShader::InputLayout::InputType input_layout_type
	);


	/**
	* @brief シェーダーファイルを破壊
	*/
	void Destroy(
		const ConstShader::VSType&register_type
	);


	/**
	* @brief シェーダーファイルを全て削除
	*/
	void DestroyEverything();


	/**
	* @brief シェーダーファイル取得
	*/
	VertexShader* GetPtr(
		const ConstShader::VSType&type
	);


private:


	/**
	* @brief インプットレイアウトデスク情報を代入する
	*/
	void SetUpInputDescList();


private:


	//! バーテックスシェーダー
	std::map<ConstShader::VSType,VertexShader*>mp_vs_list;

	//! インプットレイアウトデスクリスト
	std::map<ConstShader::InputLayout::InputType,InputDescInfo>mp_input_desc_list;

	//! 配列サイズインプットレイアウトサイズリスト

	//! 工場リスト
	std::vector<std::unique_ptr<VSFactoryBase>>mp_vs_factory_list;


};

#endif
