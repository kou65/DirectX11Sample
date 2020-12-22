#include"Triangle.h"




Triangle::Triangle(){

	m_polygon.vertex_data_size = sizeof(CustomVertexPosColor);

	SubSet subset;

	subset.count = 3;
	subset.start = 0;

	m_polygon.sub_set_list.emplace_back(subset);

	m_polygon.tepology = D3D_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


bool Triangle::Create(
	ID3D11Device* dev
) {

	if (dev == nullptr) {
		return false;
	}

	//CustomVertexPosColor cv[3];


	CustomVertexPosColor cv[]{
		{ { -0.2f,  0.2f, 0.f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  0.2f, -0.2f, 0.f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.2f, -0.2f, 0.f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	// トライアングルセット
	//SetUpTriangleVertex(cv);

	// バーテックスバッファの初期化
	if (m_polygon.vertex_buffer.Init(
		dev,
		(sizeof(CustomVertexPosColor) * 3),
		cv,
		D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER
	) == false) {
		return false;
	}

	return true;
}


void Triangle::SetUpTriangleVertex(CustomVertexPosColor cv[3]) {
	
	cv[0].pos[0] = -0.5f;
	cv[0].pos[1] = 0.5f;
	cv[0].pos[2] = 0.f;

	cv[1].pos[0] = 0.5f;
	cv[1].pos[1] = -0.5f;
	cv[1].pos[2] = 0.f;

	cv[2].pos[0] = -0.5f;
	cv[2].pos[1] = -0.5f;
	cv[2].pos[2] = 0.f;

	cv[0].col[0] = 1.f;
	cv[0].col[1] = 0.f;
	cv[0].col[2] = 0.f;
	cv[0].col[3] = 1.f;

	cv[1].col[0] = 0.f;
	cv[1].col[1] = 1.f;
	cv[1].col[2] = 0.f;
	cv[1].col[3] = 1.f;

	cv[2].col[0] = 0.f;
	cv[2].col[1] = 0.f;
	cv[2].col[2] = 1.f;
	cv[2].col[3] = 1.f;

}