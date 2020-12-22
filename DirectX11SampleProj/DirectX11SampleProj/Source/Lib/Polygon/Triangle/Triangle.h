#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include"../PolygonPrimitive/PolygonPrimitive.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../../CustomVertex/CustomVertex2D.h"



/**
* @brief Traiangle�`��
*/
class Triangle{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Triangle();


	/**
	* @brief �|���S���쐬
	*/
	bool Create(ID3D11Device* device);


	/**
	* @brief �|���S���擾
	*/
	PolygonPrimitive GetPolygon() {
		return m_polygon;
	}

private:


	/**
	* @brief �o�[�e�b�N�X���Z�b�g�A�b�v 
	*/
	void SetUpTriangleVertex(CustomVertexPosColor cv[3]);


private:

	//! �|���S�����q
	PolygonPrimitive m_polygon;

};

#endif
