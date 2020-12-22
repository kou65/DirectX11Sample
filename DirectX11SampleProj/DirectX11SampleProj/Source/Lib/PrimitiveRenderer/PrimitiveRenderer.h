#ifndef PRIMITIVE_RENDERER_H_
#define PRIMITIVE_RENDERER_H_


#include<memory>
#include<DirectXMath.h>
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../Polygon/MeshPrimitive/MeshPrimitive.h"
#include"../Shader/ConstShader/ConstShader.h"



using namespace DirectX;



/**
* @class PrimitiveRenderer
* @brief �|���S����`�悷��V���O���g���N���X
*/
class PrimitiveRenderer : public Singleton<PrimitiveRenderer>{
public:

	// �C���X�^���X�A�N�Z�X����
	friend Singleton<PrimitiveRenderer>;

public:


	/**
	* @brief ������
	*/
	bool Create();


	/**
	* @brief �|���S���`��
	*/
	void RenderingPolygon(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		PolygonPrimitive* pol,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type
	);


	/**
	* @brief �f�o�C�X�̏����g�����|���S���`��
	*/
	void RenderingPolygonByDeviceView(
		PolygonPrimitive* pol,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type
	);


	/**
	* @brief �f�o�C�X�̏����g�������b�V���`��
	*/
	void RenderingMesh(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		MeshPrimitive* mesh,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type,
		const int& vs_c_num,
		const int& ps_c_num
	);


	/**
	* @brief �f�o�C�X�̏����g�������b�V���`��
	*/
	void RenderingMeshByDeviceView(
		MeshPrimitive* mesh,
		ConstShader::VSType vs_type,
		ConstShader::PSType ps_type,
		const int& vs_c_num = 0,
		const int& ps_c_num = 0
	);


	/**
	* @brief ��n��
	*/
	void ClearRenderingInfo(
		ID3D11DeviceContext* p_context
	);


	/**
	* @brief �Z�b�g�A�b�v���X�^���C�U
	*/
	void SetUpRasterizer();


	/**
	* @brief �萔�o�b�t�@�Z�b�g
	*/
	void VSSetConstBuffer(
		ConstShader::VSType vs_type,
		int slot_num
	);


	/**
	* @brief ��o�b�t�@�Z�b�g
	*/
	void PSSetConstBuffer(
		ConstShader::PSType ps_type,
		int slot_num
	);


private:

	/**
	* @brief �B���R���X�g���N�^
	*/
	PrimitiveRenderer();

private:


	//! ���X�^���C�U�X�e�[�g
	ID3D11RasterizerState *mp_ras_state;


};


#endif
