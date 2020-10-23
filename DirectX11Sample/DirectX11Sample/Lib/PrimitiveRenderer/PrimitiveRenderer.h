#ifndef PRIMITIVE_RENDERER_H_
#define PRIMITIVE_RENDERER_H_


#include<memory>
#include"../SingletonTemplate/SingletonTemplate.h"
#include"../Polygon/PolygonPrimitive/PolygonPrimitive.h"
#include"../Polygon/MeshPrimitive/MeshPrimitive.h"
#include"../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../Shader/ShaderProcess/PixelShader/PixelShader.h"



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
	bool Init();


	/**
	* @brief �|���S���`��
	*/
	void RenderingPolygon(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		PolygonPrimitive* pol
	);


	/**
	* @brief �f�o�C�X�̏����g�����|���S���`��
	*/
	void RenderingPolygonDev(
		PolygonPrimitive* pol
	);


	/**
	* @brief �f�o�C�X�̏����g�������b�V���`��
	*/
	void RenderingMesh(
		ID3D11DeviceContext* p_context,
		ID3D11RenderTargetView* p_render_target,
		ID3D11DepthStencilView* p_depth_stencile,
		MeshPrimitive* mesh
	);

	/**
	* @brief �f�o�C�X�̏����g�������b�V���`��
	*/
	void RenderingMeshDev(
		MeshPrimitive* mesh
	);


	/**
	* @brief �Z�b�g�A�b�v���X�^���C�U
	*/
	void SetUpRasterizer();


	VertexShader* GetPtrVertexShader(){
		return mp_vs.get();
	}

private:

	/**
	* @brief �B���R���X�g���N�^
	*/
	PrimitiveRenderer();

private:

	//! ���_�V�F�[�_�[
	std::unique_ptr<VertexShader>mp_vs;

	//! �s�N�Z���V�F�[�_�[
	std::unique_ptr<PixelShader>mp_ps;

	//! ���X�^���C�U�X�e�[�g
	ID3D11RasterizerState *mp_ras_state;
};


#endif
