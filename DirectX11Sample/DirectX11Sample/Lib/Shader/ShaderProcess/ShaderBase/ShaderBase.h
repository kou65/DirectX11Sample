#ifndef SHADER_BASE_H_
#define SHADER_BASE_H_

#include<d3d11.h>
#include<stdio.h>
#include<string>
#include<wrl.h>


using namespace Microsoft::WRL;


/**
* @class ShaderBase
* @brief Shaderのbaseクラス
*/
class ShaderBase {
public:


	/**
	* @brief コンストラクタ
	*/
	ShaderBase();


	/**
	* @brief Create 作成
	* @param[out] p_device デバイスポインタ
	* @param[in] file_name ファイル名
	*/
	virtual bool Create(
		ID3D11Device*p_device,
		const std::string&file_name
	);


	inline const char* GetData()
	{
		return mp_data;
	}

	inline long GetSize()
	{
		return m_size;
	}

protected:


	/**
	* @brief ファイル読み込み
	* @param[in] file_name
	* @return int ファイルサイズを返す
	*/
	int LoadFile(
		const std::string& file_name
	);

protected:

	/**
	* @brief 型の共用体 どちらかの型を使える
	*/
	union Interface
	{
		~Interface() {};

		ID3D11VertexShader *p_vs;
		ID3D11PixelShader *p_ps;
	};

	//! ファイルデータ
	char* mp_data;

	//! ファイルサイズ
	long m_size;
};

#endif
