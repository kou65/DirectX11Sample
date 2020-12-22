#include"Quad.h"
#include"../../Math/Math.h"



Quad::Quad() {

	// 単位行列化しておく
	m_world =
		Math::TSXMMATRIX::Identity();

	m_proj =
		Math::TSXMMATRIX::Identity();

}


bool Quad::Create() {

	if (CreateStripe() == false) {
		return false;
	}

	// セットアップ
	SetUpWorld();
	SetUpProj();

	return true;
}


bool Quad::CreateStripe() {

	// ポリゴンの初期設定
	{

		SubSet v_subset;

		v_subset.count = VERTEX_COUNT;
		v_subset.start = 0;

		m_mesh.polygon_primitive.sub_set_list.emplace_back(v_subset);

		m_mesh.polygon_primitive.vertex_data_size =
			sizeof(CustomVertexPosColor);

		// トライアングルストリップ
		m_mesh.polygon_primitive.tepology =
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	}


	CustomVertexPosColor cv[VERTEX_COUNT];

	// ポリゴン形成
	CreateStripVertex(cv);

	// バーテックスバッファ
	if (m_mesh.polygon_primitive.vertex_buffer.Init(
		Device::GetInstance()->GetPtrDevice(),
		(sizeof(CustomVertexPosColor) * VERTEX_COUNT),
		cv,
		D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER
	) == false) {
		return false;
	}

	return true;
}


bool Quad::CreateList() {

	// ポリゴンの初期設定
	{

		SubSet v_subset;

		v_subset.count = VERTEX_COUNT;
		v_subset.start = 0;

		m_mesh.polygon_primitive.sub_set_list.emplace_back(v_subset);

		m_mesh.polygon_primitive.vertex_data_size =
			sizeof(CustomVertexPosColor);

		// リスト
		m_mesh.polygon_primitive.tepology =
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}


	// インデックス設定
	{
		m_mesh.format = DXGI_FORMAT::DXGI_FORMAT_R16_UINT;

		SubSet i_sub;

		i_sub.count = INDEX_COUNT;
		i_sub.start = 0;

		m_mesh.sub_set_list.emplace_back(i_sub);
	}


	CustomVertexPosColor cv[VERTEX_COUNT];

	// ポリゴン形成
	CreateListVertex(cv);

	// バーテックスバッファ
	if (m_mesh.polygon_primitive.vertex_buffer.Init(
		Device::GetInstance()->GetPtrDevice(),
		(sizeof(CustomVertexPosColor) * VERTEX_COUNT),
		cv,
		D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER
	) == false) {
		return false;
	}

	WORD index[INDEX_COUNT];

	CreateListIndex(index);

	// バーテックスバッファ
	if (m_mesh.index_buffer.Init(
		Device::GetInstance()->GetPtrDevice(),
		(sizeof(WORD) * INDEX_COUNT),
		index,
		D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER
	) == false) {
		return false;
	}

	return true;
}


void Quad::CreateStripVertex(CustomVertexPosColor cv[VERTEX_COUNT]) {

	// 右回り順に作ったポリゴンが表示される
	
	// 1番目
	{
		// 左上
		// x
		cv[0].pos[0] = MIN;
		// y
		cv[0].pos[1] = MAX;// 上(3D空間なので)
		// z
		cv[0].pos[2] = Z;

		// 左下
		cv[1].pos[0] = MIN;
		cv[1].pos[1] = MIN;
		cv[1].pos[2] = Z;

		// 右下
		cv[3].pos[0] = MAX;
		cv[3].pos[1] = MIN;
		cv[3].pos[2] = Z;

		// 右上
		cv[2].pos[0] = MAX;
		cv[2].pos[1] = MAX;
		cv[2].pos[2] = Z;

		// カラー白
		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			
			for (int j = 0; j < 3; j++) {
				cv[i].col[j] = 1.f;
			}
			cv[i].col[2] = 1.f;
		
			cv[i].col[3] = 1.f;
		}
	}
}


void Quad::CreateListVertex(CustomVertexPosColor cv[VERTEX_COUNT]) {

	cv[0].pos[0] = 0.f;
	cv[0].pos[1] = 0.f;
	cv[0].pos[2] = 0.f;

	cv[1].pos[0] = 1.f;
	cv[1].pos[1] = 0.f;
	cv[1].pos[2] = 0.f;

	cv[2].pos[0] = 0.f;
	cv[2].pos[1] = 1.f;
	cv[2].pos[2] = 0.f;

	cv[3].pos[0] = 1.f;
	cv[3].pos[1] = 1.f;
	cv[3].pos[2] = 0.f;
}


void Quad::CreateListIndex(WORD index[INDEX_COUNT]) {

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 2;
	index[4] = 1;
	index[5] = 3;
}


void Quad::SetUpWorld() {

	XMMATRIX trans;
	XMMATRIX rotation_x,rotation_y,rotation_z,total_rot;
	XMMATRIX scale;

	float rx = 0.f;
	float ry = 0.f;
	float rz = 0.f;

	float sx = 0.f;
	float sy = 0.f;
	float sz = 0.f;

	// 移動行列
	trans = 
		XMMatrixTranslation(
			rx,
			ry,
			rz
		);

	// 回転行列
	rotation_y = XMMatrixRotationY(Math::DegreesToRad(0));
	rotation_x = XMMatrixRotationX(Math::DegreesToRad(0));
	rotation_z = XMMatrixRotationZ(Math::DegreesToRad(0));

	// 合計回転
	total_rot = rotation_z * rotation_y * rotation_x;

	// 拡縮
	scale = XMMatrixScaling(sx, sy, sz);

	// ワールド座標更新
	m_world = scale * total_rot * trans;

}


void Quad::SetUpProj() {

	// ウィンドウ横幅
	const float WINDOW_WIDTH = 1920.f;

	// ウィンドウ縦幅
	const float WINDOW_HEIGHT = 1080.f;

	// 2D射影変換行列
	m_proj =
		XMMatrixTranspose(
			Math::Calc2DProj(
				WINDOW_WIDTH,
				WINDOW_HEIGHT
			)
		);
}