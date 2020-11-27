#ifndef SURFACE_2D_H_
#define SURFACE_2D_H_

#include"../MeshPrimitive/MeshPrimitive.h"
#include"../../Device/Device.h"
#include"../../CustomVertex/CustomVertex2D.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../../Shader/ShaderProcess/PixelShader/PixelShader.h"


//! DirectX�ł̃X�}�[�g�|�C���^
using namespace Microsoft::WRL;


/**
* @class Surface2D
* @brief ���ʃ|���S��
*/
class Surface2D : public MeshPrimitive{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Surface2D();


	/**
	* @brief �쐬
	*/
	bool Create(Device* dev,VertexShader*vb);

private:

	//! �ŏ��l
	const float MIN = -0.5f;

	//! �ő�l
	const float MAX = 0.5f;

	//! z�l
	const float Z = 0.f;

	//! ���_�o�b�t�@��
	static const int VERTEX_COUNT = 4;

	//! �C���f�b�N�X���X�g��
	static const int INDEX_COUNT = 6;

private:


	/**
	* @brief �|���S������
	*/
	void CreatePolygon(CustomVertexPosColor cv[VERTEX_COUNT]);


	/**
	* @brief �C���f�b�N�X���X�g�쐬
	*/
	void CreateIndexList(WORD list[INDEX_COUNT]);

};


#endif
