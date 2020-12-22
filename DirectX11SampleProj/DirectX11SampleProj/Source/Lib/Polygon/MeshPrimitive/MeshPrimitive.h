#ifndef MESH_PRIMITIVE_H_
#define MESH_PRIMITIVE_H_



#include<vector>
#include"../PolygonPrimitive/PolygonPrimitive.h"
#include"../../Buffer/BufferTemplate/BufferTemplate.h"
#include"../SubSet/SubSet.h"
#include"../../MaterialData/MaterialData.h"



/**
* @brief ���b�V�������ׂ̌p���N���X
*/
class MeshPrimitive{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	MeshPrimitive() :
		format(DXGI_FORMAT_R16_UINT)
	{};


	//! �|���S�����q
	PolygonPrimitive polygon_primitive;

	//! ���b�V���̒��ŃT�u�Z�b�g�𕪂���ׂ̃p�����[�^
	std::vector<SubSet>sub_set_list;
	
	//! 16�r�b�g��32�r�b�g���ŃC���f�b�N�X�o�b�t�@���쐬����
	DXGI_FORMAT format;

	//! �C���f�b�N�X�o�b�t�@
	BufferTemplate index_buffer;

	//! �}�e���A���f�[�^
	std::vector<MaterialData>material_data_list;
};

#endif
