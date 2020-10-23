#include"Surface2D.h"



Surface2D::Surface2D() {

	// カスタムバーテックスサイズ
	m_costom_vertex_size = sizeof(CustomVertex2D);
	m_vertex_count = VERTEX_COUNT;
	m_index_count = INDEX_COUNT;
	m_vertex_start = 0;
	m_tepology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


// セマンティクスなど設定
D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


bool Surface2D::Create(
Device*dev,
VertexShader* vs
) {

	if (dev == nullptr) {
		return false;
	}

	CustomVertex2D cv[VERTEX_COUNT];

	// ポリゴン形成
	CreatePolygon(cv);

	// バーテックスバッファ
	m_vb.Init(
		dev->GetPtrDevice(),
		(sizeof(CustomVertex2D) * VERTEX_COUNT),
		cv
	);

	WORD list[6];

	// インデックスリスト
	CreateIndexList(list);

	UINT size = (sizeof(WORD) * INDEX_COUNT);

	// インデックスバッファ
	m_ib.Init(
		dev->GetPtrDevice(),
		size,
		list
	);

	// インプットレイアウト作成
	if (FAILED(dev->GetPtrDevice()->CreateInputLayout(
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


void Surface2D::CreatePolygon(CustomVertex2D cv[VERTEX_COUNT]) {

	
	// 1番目
	{
		// 左下
		// x
		cv[0].pos[0] = MIN;
		// y
		cv[0].pos[1] = MIN;
		// z
		cv[0].pos[2] = Z;

		// 右
		cv[1].pos[0] = MAX;
		cv[1].pos[1] = MIN;
		cv[1].pos[2] = Z;

		// 左
		cv[2].pos[0] = MAX;
		cv[2].pos[1] = MAX;
		cv[2].pos[2] = Z;

		// 右下
		cv[3].pos[0] = MIN;
		cv[3].pos[1] = MAX;
		cv[3].pos[2] = Z;

		// カラー白
		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			
			for (int j = 0; j < 3; j++) {
				cv[i].col[j] = 0.f;
			}
			cv[i].col[2] = 1.f;
		
			cv[i].col[3] = 1.f;
		}
	}
}


void Surface2D::CreateIndexList(WORD list[INDEX_COUNT]) {

	list[0] = 0;
	list[1] = 1;
	list[2] = 2;
	list[3] = 0;
	list[4] = 2;
	list[5] = 3;
}