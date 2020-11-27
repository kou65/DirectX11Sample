#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include<map>
#include<memory>
#include<vector>

#include"../../SingletonTemplate/SingletonTemplate.h"
#include"../ShaderProcess/PixelShader/PixelShader.h"
#include"../ConstantShader/ConstantShader.h"
#include"../Factory/PSFactoryBase/PSFactoryBase.h"



/**
* @class PixelShaderManager
* @brief 頂点シェーダーを管理するクラス
*/
class PixelShaderManager : public Singleton<PixelShaderManager> {
public:


	friend class Singleton<PixelShaderManager>;


	/**
	* @brief コンストラクタ
	*/
	PixelShaderManager();


	/**
	* @brief デストラクタ
	*/
	~PixelShaderManager();


	/**
	* @brief シェーダファイル生成
	*/
	bool Create(
		const std::string& cso_file_name,
		ConstantShader::PSType register_type
	);


	/**
	* @brief シェーダーファイルを破壊
	*/
	void Destroy(
		ConstantShader::PSType register_type
	);


	/**
	* @brief シェーダーファイルを全て削除
	*/
	void DestroyEverything();


	/**
	* @brief シェーダーファイル取得
	*/
	PixelShader* GetPtr(
		ConstantShader::PSType type
	);


private:


	//! ピクセルシェーダー管理者
	std::map<ConstantShader::PSType,PixelShader*>mp_ps_list;

	//! ピクセルシェーダー生成者リスト
	std::vector<std::unique_ptr<PSFactoryBase>>mp_ps_factory_list;


};

#endif
