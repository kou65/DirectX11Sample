#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_


#include<d3d11.h>
#include<wrl.h>

//! DirectX版のスマートポインタ
using namespace Microsoft::WRL;



/**
* @class IndexBuffer
* @brief インデックスバッファ
*/
class IndexBuffer {
public:

	IndexBuffer();
	~IndexBuffer();


	bool Init(
		ID3D11Device* dev,
		UINT size,
		void* custom_vertex_list
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

	ID3D11Buffer *mp_buffer;
};

#endif
