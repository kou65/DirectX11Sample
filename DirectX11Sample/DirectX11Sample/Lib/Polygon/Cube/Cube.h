#ifndef CUBE_H_
#define CUBE_H_

#include<d3d11.h>
#include<DirectXMath.h>
#include"../MeshPrimitive/MeshPrimitive.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"



using namespace DirectX;

/**
* @class Cube
* @brief �L���[�u
*/
class Cube : public MeshPrimitive{
public:


	/**
	* @brief �쐬
	*/
	bool Create(
		ID3D11Device* dev,
		VertexShader* vb
	);


	void IndexListSet(WORD list[36]);

private:

	// ���[���h�s��
	XMMATRIX world_mat;

	// �r���[�s��
	XMMATRIX view_mat;

	// �ˉe�s��
	XMMATRIX proj_mat;
};

#endif
