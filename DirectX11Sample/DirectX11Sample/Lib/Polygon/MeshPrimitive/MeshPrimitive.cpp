#include"MeshPrimitive.h"



MeshPrimitive::MeshPrimitive(
	UINT costom_vertex_size,
	UINT vertex_count,
	UINT vertex_start,
	UINT index_count,
	D3D_PRIMITIVE_TOPOLOGY tepology
) : PolygonPrimitive(
	costom_vertex_size,
	vertex_count,
	vertex_start,
	tepology
),
m_index_count(index_count)
{

}


UINT MeshPrimitive::GetIndexCount() {
	return m_index_count;
}


Buffer *MeshPrimitive::GetIndexBuffer() {
	return &m_index_buffer;
}
