#include"Cube.h"
#include"../../CustomVertex/CustomVertex2D.h"
#include"../../CustomVertex/CustomVertexPosNorCol.h"
#include"../../CustomVertex/CustomVertex2D.h"
#include"../../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../../Math/Math.h"



Cube::Cube(
	Camera3D* p_camera
) : MeshPrimitive(
sizeof(CustomVertexPosNorCol),VERTEX_COUNT,0,INDEX_COUNT 
){

	m_camera = p_camera;
	m_pos = XMFLOAT3(0.f, 0.f, 0.f);
}


void Cube::InitIndexList(WORD list[36]) {

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


CustomVertexPosNorCol g_VertexList[]{
	{ { -0.5f,  0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ {  0.5f,  0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 0.0f, 1.0f } },
	{ {  0.5f, -0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 0.0f, 1.0f } },
							   
	{ { -0.5f,  0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 1.0f, 1.0f } },
	{ { -0.5f, -0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 1.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 1.0f, 1.0f } },
							   
	{ { -0.5f,  0.5f,  0.5f }, {1.f,1.f,1.f},{ 1.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f,  0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f,  0.5f }, {1.f,1.f,1.f},{ 1.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 1.0f, 0.0f, 1.0f } },

	{ {  0.5f,  0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f, -0.5f }, {1.f,1.f,1.f},{ 0.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f, -0.5f, -0.5f }, {1.f,1.f,1.f},{ 0.0f, 0.0f, 1.0f, 1.0f } },

	{ { -0.5f,  0.5f,  0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f,  0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 1.0f, 1.0f } },
	{ { -0.5f,  0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 1.0f, 1.0f } },
	{ {  0.5f,  0.5f, -0.5f }, {1.f,1.f,1.f},{ 1.0f, 0.0f, 1.0f, 1.0f } },

	{ { -0.5f, -0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ { -0.5f, -0.5f, -0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ {  0.5f, -0.5f,  0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 0.0f, 1.0f } },
	{ {  0.5f, -0.5f, -0.5f }, {1.f,1.f,1.f},{ 0.0f, 1.0f, 0.0f, 1.0f } },
};

bool Cube::Create(
	ID3D11Device* dev,
	VertexShader* vs
) {

	if (dev == nullptr) {
		return false;
	}

	// バーテックスバッファ
	m_vertex_buffer.Init(
		dev,
		(sizeof(CustomVertexPosNorCol) * VERTEX_COUNT),
		g_VertexList,
		D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER
	);

	WORD list[36];

	// インデックスリストセット
	InitIndexList(list);

	// インデックスバッファ
	m_index_buffer.Init(
		dev,                                     // デバイス
		(sizeof(WORD) * INDEX_COUNT),            // サイズ
		list,                                    // インデックスリスト
		D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER // バッファの使い方
	);

	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,4*3,0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, ((4 * 3) + (4 * 3)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
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


void Cube::Update(
	VertexShader* vs
) {

	// 定数バッファ
	SetUpConstBuffer(
		vs
	);
}


void Cube::SetUpConstBuffer(
	VertexShader*p_vs
) {

	// ワールド行列
	XMMATRIX world_matrix = 
		XMMatrixTranslation(
			m_pos.x,
			m_pos.y,
			m_pos.z
		);

	XMStoreFloat4x4(&m_ts_data.world, XMMatrixTranspose(world_matrix));
	m_ts_data.view = m_camera->GetViewTransposeMatrix();
	m_ts_data.projection = m_camera->GetProjTransposeMatrix();

	// リソースデータを受け取る
	Device::GetInstance()->GetPtrImmContext()->
		UpdateSubresource(
		p_vs->GetConstBuffer()->GetBuffer(),
		0,
		NULL,
		&m_ts_data,
		0,
		0
	);

}

