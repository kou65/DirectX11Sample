#include"Triangle.h"




Triangle::Triangle() : PolygonPrimitive(
	sizeof(CustomVertexPosColor),3,0, 
	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
){
}


bool Triangle::Create(
	ID3D11Device* dev, 
	VertexShader* vs
) {

	if (dev == nullptr) {
		return false;
	}

	//CustomVertexPosColor cv[3];


	CustomVertexPosColor cv[]{
		{ { -0.2f,  0.2f, 0.2f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  0.2f, -0.2f, 0.2f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.2f, -0.2f, 0.2f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	// トライアングルセット
	//SetUpTriangleVertex(cv);

	// バーテックスバッファのデスク作成
	D3D11_BUFFER_DESC vbd;

	// バッファのサイズ
	vbd.ByteWidth = sizeof(CustomVertexPosColor) * (3);
	// 使用方法
	vbd.Usage = D3D11_USAGE_DEFAULT;
	// バッファの種類(頂点バッファ)
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPUアクセス設定
	vbd.CPUAccessFlags = 0;
	// その他のオプション
	vbd.MiscFlags = 0;
	// 構造体のサイズ
	vbd.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA v_init_data;

	// 頂点バッファの初期値
	v_init_data.pSysMem = cv;
	// 頂点バッファでは使用しない
	v_init_data.SysMemPitch = 0;
	v_init_data.SysMemSlicePitch = 0;

	HRESULT hr = NULL;

	// バーテックスバッファの初期化
	if (m_vertex_buffer.Init(
		dev,
		(sizeof(CustomVertexPosColor) * 3),
		cv,
		D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER
	) == false) {
		return false;
	}

// セマンティクスなど設定
D3D11_INPUT_ELEMENT_DESC g_vertexDesc[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,   0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

	// インプットレイアウト作成
	if (dev->CreateInputLayout(
		g_vertexDesc,
		ARRAYSIZE(g_vertexDesc),
		vs->GetData(),
		vs->GetSize(),
		&mp_il
	) != S_OK
		) {

		return false;
	}

	return true;
}


void Triangle::SetUpTriangleVertex(CustomVertexPosColor cv[3]) {
	
	cv[0].pos[0] = -0.5f;
	cv[0].pos[1] = 0.5f;
	cv[0].pos[2] = 0.5f;

	cv[1].pos[0] = 0.5f;
	cv[1].pos[1] = -0.5f;
	cv[1].pos[2] = 0.5f;

	cv[2].pos[0] = -0.5f;
	cv[2].pos[1] = -0.5f;
	cv[2].pos[2] = 0.5f;

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