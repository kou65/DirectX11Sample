#ifndef MESH_PRIMITIVE_H_
#define MESH_PRIMITIVE_H_

#include"../PolygonPrimitive/PolygonPrimitive.h"
#include"../../Buffer/Buffer.h"

/**
* @class MeshPrimitive
* @brief ���b�V�������ׂ̌p���N���X
*/
class MeshPrimitive : public PolygonPrimitive{
public:


	MeshPrimitive(
		UINT costom_vertex_size,
		UINT vertex_count,
		UINT vertex_start,
		UINT index_count,
		D3D_PRIMITIVE_TOPOLOGY tepology =
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);


	UINT GetIndexCount();


	Buffer *GetIndexBuffer();


protected:

	UINT m_index_count;

	// �C���f�b�N�X�o�b�t�@
	Buffer m_index_buffer;
};

#endif
