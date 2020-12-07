#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include<map>
#include<vector>
#include<memory>
#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/VertexShader/VertexShader.h"
#include"../ConstantShader/ConstantShader.h"
#include"../Factory/VSFactoryBase/VSFactoryBase.h"



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
		const std::string& cso_file_name,
		ConstantShader::VSType register_type
	);


	/**
	* @brief シェーダーファイルを破壊
	*/
	void Destroy(
		ConstantShader::VSType register_type
	);


	/**
	* @brief シェーダーファイルを全て削除
	*/
	void DestroyEverything();


	/**
	* @brief シェーダーファイル取得
	*/
	VertexShader* GetPtr(
		ConstantShader::VSType type
	);


private:


	//! バーテックスシェーダー
	std::map<ConstantShader::VSType,VertexShader*>mp_vs_list;

	//! 工場リスト
	std::vector<std::unique_ptr<VSFactoryBase>>mp_vs_factory_list;
};

#endif
