#include"Cube.h"
#include"../../CustomVertex/CustomVertex2D.h"



void Cube::IndexListSet(WORD list[36]) {

	list[0] = 0;
	list[1] = 1;
	list[2] = 2;
	list[3] = 3;
	list[4] = 2;
	list[5] = 1;

	list[6] = 4;
	list[7] = 5;
	list[8] = 6;
	list[9] = 7;
	list[10] = 6;
	list[11] = 5;

	list[12] = 8;
	list[13] = 9;
	list[14] = 10;
	list[15] = 11;
	list[16] = 10;
	list[17] = 9;

	list[18] = 12;
	list[19] = 13;
	list[20] = 14;
	list[21] = 15;
	list[22] = 14;
	list[23] = 13;

	list[24] = 16;
	list[25] = 17;
	list[26] = 18;
	list[27] = 19;
	list[28] = 18;
	list[29] = 17;

	list[30] = 20;
	list[31] = 21;
	list[32] = 22;
	list[33] = 23;
	list[34] = 22;
	list[35] = 21;

}


CustomVertex2D g_VertexList[]{
	{ { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
	{ {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f } },

	{ { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	{ { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f } },

	{ { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f } },

	{ {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f } },

	{ { -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	{ { -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f } },

	{ { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	{ {  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
};

bool Cube::Create(
	ID3D11Device* dev,
	VertexShader* vs
) {


	if (dev == nullptr) {
		return false;
	}


	// バーテックスバッファ
	m_vb.Init(
		dev,
		(sizeof(CustomVertex2D) * 24),
		g_VertexList
	);

	WORD list[36];

	// インデックスリスト
	IndexListSet(list);

	UINT size = (sizeof(WORD) * 36);

	// インデックスバッファ
	m_ib.Init(
		dev,
		size,
		list
	);

	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// インプットレイアウト作成
	if (FAILED(dev->CreateInputLayout(
		g_VertexDesc,
		ARRAYSIZE(g_VertexDesc),
		vs->GetData(),
		vs->GetSize(),
		&mp_il
	))
		) {

		return false;
	}

	return true;
}