#ifndef CONSTANT_SHADER_H_
#define CONSTANT_SHADER_H_



#include<d3d11.h>



/**
* @brief 定数シェーダー空間
*/
namespace ConstShader {


	/**
	* brief シェーダーの種類
	*/
	enum class ShaderType {
		VERTEX,
		PIXEL
	};


	/**
	* @enum Type
	* @brief 頂点シェーダーの種類
	*/
	enum class VSType {
		NORMAL,
		VS2D,
		VS3D,
		VARIOUS_LIGHT,
		TOTAL,
	};


	/**
	* @enum Type
	* @brief 頂点シェーダーの種類
	*/
	enum class PSType {
		NORMAL,
		VARIOUS_LIGHT,
		TOTAL,
	};


	/**
	* @brief インプットレイアウト関係の定数
	*/
	namespace InputLayout {


		/**
		* @brief インプットレイアウトの識別番号
		*/
		enum class InputType {
			VER_NOR,
			VER_COL,
			VER_NOR_COL
		};


		static const int VER_NOR_DESC_ARRAY_SIZE = 2;


		/**
		* @brief 頂点法線
		*/
		const D3D11_INPUT_ELEMENT_DESC VER_NOR_DESC[]{
			{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};


		static const int VER_COL_DESC_ARRAY_SIZE = 2;


		/**
		* @brief 頂点カラー
		*/
		const D3D11_INPUT_ELEMENT_DESC VER_COL_DESC[]{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};


		static const int VER_NOR_COL_DESC_ARRAY_SIZE = 3;


		/**
		* @brief 頂点法線カラー
		*/
		const D3D11_INPUT_ELEMENT_DESC VER_NOR_COL_DESC[]{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,   0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,4 * 3,0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, ((4 * 3) + (4 * 3)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	}
}

#endif
