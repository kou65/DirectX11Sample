#ifndef POLYGON_PRIMITIVE_H_
#define POLYGON_PRIMITIVE_H_

#include<d3d11.h>
#include<Wrl.h>
#include"../../Buffer/Buffer.h"


//! DirectX�ł̃X�}�[�g�|�C���^
using namespace Microsoft::WRL;


/**
* @class PolygonPrimitive
* @brief �|���S���̌��q
*/
class PolygonPrimitive {
public:


	/**
	* @brief �R���X�g���N�^
	*/
	PolygonPrimitive(
		UINT m_costom_vertex_size,
		UINT m_vertex_count,
		UINT m_vertex_start,
		D3D_PRIMITIVE_TOPOLOGY m_tepology = 
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	);


	/**
	* @brief �J�X�^���o�[�e�b�N�X��sizeof�ȂǂŃT�C�Y�𑪂����T�C�Y
	*/
	UINT GetCustomVertexSize();


	/**
	* @brief ���_����Ԃ�
	*/
	UINT GetVertexCount();


	/**
	* @brief ���_�ŏ�
	*/
	UINT GetStartVertex();


	/**
	* @brief �`���Ԃ�
	*/
	D3D_PRIMITIVE_TOPOLOGY GetPrimitive();


	/**
	* @brief VertexBuffer��Ԃ�
	*/
	Buffer *GetVertexBuffer();


	/**
	* @brief �C���v�b�g���C�A�E�g�̃|�C���^��Ԃ�
	*/
	ID3D11InputLayout *GetPtrInputLayout();

protected:

	Buffer m_vertex_buffer;
	ID3D11InputLayout *mp_il;

	UINT m_costom_vertex_size;
	UINT m_vertex_count;
	UINT m_vertex_start;
	D3D_PRIMITIVE_TOPOLOGY m_tepology;
};

#endif
