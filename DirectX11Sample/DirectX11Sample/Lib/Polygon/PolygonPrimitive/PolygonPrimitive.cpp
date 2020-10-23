#include"PolygonPrimitive.h"
#include"../../CustomVertex/CustomVertex2D.h"



PolygonPrimitive::PolygonPrimitive() {

	m_costom_vertex_size = sizeof(CustomVertex2D);
	m_vertex_count = 3;
	m_vertex_start = 0;
	m_tepology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
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


VertexBuffer PolygonPrimitive::GetVertexBuffer() {
	return m_vb;
}


ComPtr<ID3D11InputLayout> PolygonPrimitive::GetPtrInputLayout() {
	return mp_il;
}
