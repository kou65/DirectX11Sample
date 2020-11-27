#include"PolygonPrimitive.h"
#include"../../CustomVertex/CustomVertex2D.h"



PolygonPrimitive::PolygonPrimitive(
	UINT costom_vertex_size,
	UINT vertex_count,
	UINT vertex_start,
	D3D_PRIMITIVE_TOPOLOGY tepology
) : 
m_costom_vertex_size(costom_vertex_size),
m_vertex_count(vertex_count),
m_vertex_start(vertex_start),
m_tepology(tepology) 
{
	mp_il = nullptr;
}


UINT PolygonPrimitive::GetCustomVertexSize() {

	return m_costom_vertex_size;
}


UINT PolygonPrimitive::GetVertexCount() {

	return m_vertex_count;
}


UINT PolygonPrimitive::GetStartVertex() {

	return m_vertex_start;
}


D3D_PRIMITIVE_TOPOLOGY PolygonPrimitive::GetPrimitive() {
	return m_tepology;
}


Buffer *PolygonPrimitive::GetVertexBuffer() {
	return &m_vertex_buffer;
}


ID3D11InputLayout *PolygonPrimitive::GetPtrInputLayout() {
	return mp_il;
}
