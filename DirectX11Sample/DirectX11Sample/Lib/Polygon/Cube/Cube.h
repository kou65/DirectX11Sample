#ifndef CUBE_H_
#define CUBE_H_

#include<d3d11.h>
#include<DirectXMath.h>
#include"../MeshPrimitive/MeshPrimitive.h"
#include"../../Shader/ShaderProcess/VertexShader/VertexShader.h"
#include"../../Shader/ShaderProcess/PixelShader/PixelShader.h"
#include"../../Buffer/Buffer.h"
#include"../../LightConstBuffer/LightConstBuffer.h"



using namespace DirectX;



/**
* @class Cube
* @brief キューブ
*/
class Cube : public MeshPrimitive{
public:


	Cube();


	/**
	* @brief 作成
	*/
	bool Create(
		ID3D11Device* dev,
		VertexShader* vb
	);


	void InitIndexList(WORD list[36]);

private:

	void SetUpConstBuffer(
		float aspect_width,
		float aspect_height,
		VertexShader* p_vs
	);

	void SetUpLightDataConstBuffer(
		float aspect_width,
		float aspect_height,
		VertexShader* p_vs,
		PixelShader* p_ps
	);

	void SetCamera();

private:

	static const int VERTEX_COUNT = 24;
	static const int INDEX_COUNT = 36;

private:

	// ワールド行列
	XMMATRIX world_mat;

	// ビュー行列
	XMMATRIX view_mat;

	// 射影行列
	XMMATRIX proj_mat;


	LightConstBuffer m_lc_buffer;
};

#endif
