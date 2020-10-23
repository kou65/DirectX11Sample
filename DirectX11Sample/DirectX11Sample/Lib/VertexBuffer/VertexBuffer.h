#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include<d3d11.h>
#include<wrl.h>

//! DirectX版のスマートポインタ
using namespace Microsoft::WRL;


/**
* @class VertexBuffer
* @brief バーテックスバッファ
*/
class VertexBuffer {
public:

	VertexBuffer();
	~VertexBuffer();


	bool Init(
		ID3D11Device* dev,
		UINT size,
		void *custom_vertex_list
	);


	bool Init(
		ID3D11Device* dev,
		const D3D11_BUFFER_DESC& desc,
		const D3D11_SUBRESOURCE_DATA& res_data
	);


	bool Init(
		ID3D11Device* dev,
		const D3D11_BUFFER_DESC& desc,
		void* custom_vertex_list
	);


	void Release();
	ID3D11Buffer *GetBuffer();

private:

	ID3D11Buffer *mp_vertex_buffer;
};

/*
座標
法線
カラー
テクスチャuv
影響するボーン
ウェイト
*/

#endif
