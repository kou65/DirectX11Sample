#ifndef SHADER_BASE_H_
#define SHADER_BASE_H_

#include<d3d11.h>
#include<stdio.h>
#include<string>
#include<wrl.h>
#include"../../../Buffer/Buffer.h"



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
	* @brief 仮想デストラクタ
	*/
	virtual ~ShaderBase();


	/**
	* @brief Create 作成
	* @param[out] p_device デバイスポインタ
	* @param[in] file_name ファイル名
	*/
	virtual bool Create(
		ID3D11Device*p_device,
		const std::string&file_name
	);


	/**
	* @brief データ
	*/
	inline const char* GetData()
	{
		return mp_data;
	}


	/**
	* @brief サイズ
	*/
	inline long GetSize()
	{
		return m_size;
	}


	/**
	* @brief 定数バッファを返す
	*/
	Buffer *GetConstBuffer();


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

	// 定数バッファ
	Buffer m_const_buffer;
};

#endif
