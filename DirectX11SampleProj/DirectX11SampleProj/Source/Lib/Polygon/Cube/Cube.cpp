#include"Cube.h"
#include"../../CustomVertex/CustomVertex2D.h"
#include"../../CustomVertex/CustomVertexPosNorCol.h"
#include"../../CustomVertex/CustomVertex2D.h"
#include"../../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../../Math/Math.h"



Cube::Cube(Camera3D* p_camera) :
	m_camera(p_camera),
	m_pos(XMFLOAT3(0.f, 0.f, 0.f))
{
	m_mesh.polygon_primitive.vertex_data_size = 
		sizeof(CustomVertexPosNorCol);

	SubSet v_subset;

	v_subset.start = 0;
	v_subset.count = VERTEX_COUNT;

	m_mesh.polygon_primitive.sub_set_list.emplace_back(v_subset);

	SubSet subset;

	// 0から始める
	subset.start = 0;
	subset.count = INDEX_COUNT;

	m_mesh.sub_set_list.emplace_back(subset);
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
	ID3D11Device* dev
) {

	if (dev == nullptr) {
		return false;
	}

	// バーテックスバッファ
	m_mesh.polygon_primitive.vertex_buffer.Init(
		dev,
		(sizeof(CustomVertexPosNorCol) * VERTEX_COUNT),
		g_VertexList,
		D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER
	);

	WORD list[36];

	// インデックスリストセット
	InitIndexList(list);

	// インデックスバッファ
	m_mesh.index_buffer.Init(
		dev,                                     // デバイス
		(sizeof(WORD) * INDEX_COUNT),            // サイズ
		list,                                    // インデックスリスト
		D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER // バッファの使い方
	);



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

	// 0番目のスロット定数バッファを使う
	ID3D11Buffer* p_vsb =
		p_vs->GetConstBuffer(0);


	// リソースデータを送る
	Device::GetInstance()->GetPtrImmContext()->
		UpdateSubresource(
		p_vsb,
		0,
		NULL,
		&m_ts_data,
		0,
		0
	);

}

