#include"MeshPrimitive.h"



UINT MeshPrimitive::GetIndexCount() {
	return m_index_count;
}



IndexBuffer MeshPrimitive::GetIndexBuffer() {
	return m_ib;
}