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
* @brief ���ʃ|���S��
*/
class Quad{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Quad();


	/**
	* @brief �쐬
	*/
	bool Create();


	/**
	* @brief �|���S����Ԃ�
	*/
	PolygonPrimitive GetPolygon() {
		return m_mesh.polygon_primitive;
	}


	/**
	* @brief �|���S����Ԃ�
	*/
	MeshPrimitive GetMesh() {
		return m_mesh;
	}


private:

	//! �ŏ��l
	const float MIN = 0.f;

	//! �ő�l
	const float MAX = 1.f;

	//! z�l
	const float Z = 0.f;

	//! ���_�o�b�t�@��
	static const int VERTEX_COUNT = 4;

	//! �C���f�b�N�X���X�g��
	static const int INDEX_COUNT = 6;

private:


	bool CreateStripe();


	bool CreateList();


	/**
	* @brief �|���S������
	*/
	void CreateStripVertex(CustomVertexPosColor cv[VERTEX_COUNT]);


	/**
	* @brief ���X�g�p�|���S������
	*/
	void CreateListVertex(CustomVertexPosColor cv[VERTEX_COUNT]);


	/**
	* @brief ���X�g�p�C���f�b�N�X����
	*/
	void CreateListIndex(WORD index[INDEX_COUNT]);


	/**
	* @brief �Z�b�g�A�b�v�ˉe�ϊ�
	*/
	void SetUpProj();


	/**
	* @brief �Z�b�g�A�b�v���[���h���W
	*/
	void SetUpWorld();


private:


	//! ���b�V�����q
	MeshPrimitive m_mesh;

	//! ���[���h�s��
	XMMATRIX m_world;

	//! �ˉe�s��
	XMMATRIX m_proj;


};


#endif
