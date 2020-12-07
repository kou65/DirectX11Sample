#ifndef CUBE_H_
#define CUBE_H_

#include<d3d11.h>
#include<DirectXMath.h>
#include"../MeshPrimitive/MeshPrimitive.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../../Shader/ShaderProcess/PixelShader/PixelShader.h"
#include"../../Buffer/Buffer.h"
#include"../../LightConstBuffer/LightConstBuffer.h"
#include"../../Camera3D/Camera3D.h"
#include"../../TransformMatrixData3D/TransformMatrixData3D.h"



using namespace DirectX;



/**
* @class Cube
* @brief �L���[�u
*/
class Cube : public MeshPrimitive{
public:


	/**
	* @brief �R���X�g���N�^
	*/
	Cube(
		Camera3D* p_camera
	);


	/**
	* @brief �쐬
	*/
	bool Create(
		ID3D11Device* dev,
		VertexShader* vb
	);


	/**
	* @brief �C���f�b�N�X���X�g�Z�b�g
	*/
	void InitIndexList(WORD list[36]);


	/**
	* @brief �X�V�֐�
	*/
	void Update(
		VertexShader* vs
	);


	/**
	* @brief �ϊ��s���Ԃ�
	*/
	TS3DMatrixData GetTSMatrix(){
		return m_ts_data;
	}


private:


	/**
	* @brief �Z�b�g�A�b�v�萔�o�b�t�@
	*/
	void SetUpConstBuffer(
		VertexShader* p_vs
	);


private:

	static const int VERTEX_COUNT = 24;
	static const int INDEX_COUNT = 36;

private:

	// ���݈ʒu
	XMFLOAT3 m_pos;

	// �s��ϊ��p
	TS3DMatrixData m_ts_data;

	// �J����
	Camera3D *m_camera;
};

#endif
