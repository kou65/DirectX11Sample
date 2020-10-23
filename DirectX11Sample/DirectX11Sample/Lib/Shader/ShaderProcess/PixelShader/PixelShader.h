#ifndef PIXEL_SHADER_H_
#define PIXEL_SHADER_H_

#include"../ShaderBase/ShaderBase.h"


class PixelShader : public ShaderBase{
public:


	/**
	* @brief コンストラクタ
	*/
	PixelShader();


	/**
	* @brief デストラクタ
	*/
	virtual ~PixelShader();


	/**
	* @brief 作成
	*/
	virtual bool Create(
		ID3D11Device* p_device,
		const std::string& file_name
	);


	/**
	* @brief インターフェースptrを返す
	*/
	ID3D11PixelShader *GetInterfacePtr();

private:

	ID3D11PixelShader *mp_ps;
};

#endif
