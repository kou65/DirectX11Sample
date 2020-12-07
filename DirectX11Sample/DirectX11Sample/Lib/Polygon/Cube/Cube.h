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
* @brief キューブ
*/
class Cube : public MeshPrimitive{
public:


	/**
	* @brief コンストラクタ
	*/
	Cube(
		Camera3D* p_camera
	);


	/**
	* @brief 作成
	*/
	bool Create(
		ID3D11Device* dev,
		VertexShader* vb
	);


	/**
	* @brief インデックスリストセット
	*/
	void InitIndexList(WORD list[36]);


	/**
	* @brief 更新関数
	*/
	void Update(
		VertexShader* vs
	);


	/**
	* @brief 変換行列を返す
	*/
	TS3DMatrixData GetTSMatrix(){
		return m_ts_data;
	}


private:


	/**
	* @brief セットアップ定数バッファ
	*/
	void SetUpConstBuffer(
		VertexShader* p_vs
	);


private:

	static const int VERTEX_COUNT = 24;
	static const int INDEX_COUNT = 36;

private:

	// 現在位置
	XMFLOAT3 m_pos;

	// 行列変換用
	TS3DMatrixData m_ts_data;

	// カメラ
	Camera3D *m_camera;
};

#endif
