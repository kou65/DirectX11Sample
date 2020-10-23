#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include<d3d11.h>
#include<wrl.h>

//! DirectX�ł̃X�}�[�g�|�C���^
using namespace Microsoft::WRL;


/**
* @class VertexBuffer
* @brief �o�[�e�b�N�X�o�b�t�@
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
���W
�@��
�J���[
�e�N�X�`��uv
�e������{�[��
�E�F�C�g
*/

#endif
