#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include"../PolygonPrimitive/PolygonPrimitive.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../../CustomVertex/CustomVertex2D.h"


/**
* @class Traiangle
* @brief Traiangle�`��
*/
class Triangle : public PolygonPrimitive{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Triangle();


	bool Create(ID3D11Device* device, 
		VertexShader* vertex_shader);

private:


	void SetUpTriangleVertex(CustomVertexPosColor cv[3]);

private:
};

#endif
