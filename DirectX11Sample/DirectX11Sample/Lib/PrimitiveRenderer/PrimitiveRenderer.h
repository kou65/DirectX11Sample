#ifndef PRIMITIVE_RENDERER_H_
#define PRIMITIVE_RENDERER_H_


#include<memory>
#include<DirectXMath.h>
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../Polygon/PolygonPrimitive/PolygonPrimitive.h"
#include"../Polygon/MeshPrimitive/MeshPrimitive.h"
#include"../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../Shader/ConstantShader/ConstantShader.h"



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
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
	);


	/**
	* @brief �f�o�C�X�̏����g�����|���S���`��
	*/
	void RenderingPolygonByDeviceView(
		PolygonPrimitive* pol,
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
	);


	/**
	* @brief �f�o�C�X�̏����g�������b�V���`��
	*/
	void RenderingMesh(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		MeshPrimitive* mesh,
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
	);


	/**
	* @brief �f�o�C�X�̏����g�������b�V���`��
	*/
	void RenderingMeshByDeviceView(
		MeshPrimitive* mesh,
		ConstantShader::VSType vs_type,
		ConstantShader::PSType ps_type
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
