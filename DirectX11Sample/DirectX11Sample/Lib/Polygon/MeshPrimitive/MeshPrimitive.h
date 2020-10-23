#ifndef MESH_PRIMITIVE_H_
#define MESH_PRIMITIVE_H_

#include"../PolygonPrimitive/PolygonPrimitive.h"
#include"../../IndexBuffer/IndexBuffer.h"

/**
* @class MeshPrimitive
* @brief ���b�V�������ׂ̌p���N���X
*/
class MeshPrimitive : public PolygonPrimitive{
public:

	UINT GetIndexCount();

	IndexBuffer GetIndexBuffer();

protected:

	UINT m_index_count;
	IndexBuffer m_ib;
};

#endif
