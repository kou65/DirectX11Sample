#ifndef VS3D_H_
#define VS3D_H_

#include"../VertexShader/VertexShader.h"
#include<DirectXMath.h>


using namespace DirectX;


/**
* @brief 頂点シェーダー3D
*/
class VS3D : public VertexShader{
public:

	void SetWorldMatrix();
	void SetViewMatrix();
	void SetProjMatrix();

private:

	XMMATRIX m_world_matrix;
	XMMATRIX m_view_matrix;
	XMMATRIX m_proj_matrix;
};


#endif
