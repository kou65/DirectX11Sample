#ifndef CONSTANT_SHADER_H_
#define CONSTANT_SHADER_H_



#include<d3d11.h>



/**
* @brief �萔�V�F�[�_�[���
*/
namespace ConstShader {


	/**
	* brief �V�F�[�_�[�̎��
	*/
	enum class ShaderType {
		VERTEX,
		PIXEL
	};


	/**
	* @enum Type
	* @brief ���_�V�F�[�_�[�̎��
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
	* @brief ���_�V�F�[�_�[�̎��
	*/
	enum class PSType {
		NORMAL,
		VARIOUS_LIGHT,
		TOTAL,
	};


	/**
	* @brief �C���v�b�g���C�A�E�g�֌W�̒萔
	*/
	namespace InputLayout {


		/**
		* @brief �C���v�b�g���C�A�E�g�̎��ʔԍ�
		*/
		enum class InputType {
			VER_NOR,
			VER_COL,
			VER_NOR_COL
		};


		static const int VER_NOR_DESC_ARRAY_SIZE = 2;


		/**
		* @brief ���_�@��
		*/
		const D3D11_INPUT_ELEMENT_DESC VER_NOR_DESC[]{
			{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};


		static const int VER_COL_DESC_ARRAY_SIZE = 2;


		/**
		* @brief ���_�J���[
		*/
		const D3D11_INPUT_ELEMENT_DESC VER_COL_DESC[]{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};


		static const int VER_NOR_COL_DESC_ARRAY_SIZE = 3;


		/**
		* @brief ���_�@���J���[
		*/
		const D3D11_INPUT_ELEMENT_DESC VER_NOR_COL_DESC[]{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,   0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,4 * 3,0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, ((4 * 3) + (4 * 3)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	}
}

#endif
