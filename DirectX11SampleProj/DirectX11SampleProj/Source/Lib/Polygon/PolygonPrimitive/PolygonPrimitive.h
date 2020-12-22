#ifndef POLYGON_PRIMITIVE_H_
#define POLYGON_PRIMITIVE_H_

#include<d3d11.h>
#include<vector>
#include"../../Buffer/BufferTemplate/BufferTemplate.h"
#include"../SubSet/SubSet.h"



/**
* @brief �|���S���̌��q
*/
struct PolygonPrimitive {


	/**
	* @brief �R���X�g���N�^
	*/
	PolygonPrimitive() : 
		tepology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
		vertex_data_size(0)
	{}


	//! ���_�o�b�t�@
	BufferTemplate vertex_buffer;

	//! ���_�f�[�^�T�C�Y
	UINT vertex_data_size;

	//! �T�u�Z�b�g���X�g
	std::vector<SubSet>sub_set_list;

	//! �`�����@
	D3D_PRIMITIVE_TOPOLOGY tepology;


};

#endif
