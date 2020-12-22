#include"CreateShader.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"
#include"../Shader/ConstShader/ConstShader.h"
#include"../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../ConstBufferData/LightConstBuffer/LightConstBuffer.h"
#include"../ConstBufferData/VS2DData/VS2DData.h"



namespace CreateShader {


	void Create() {

		CreateVS();
		InitConstVS();


		CreatePS();
		InitConstPS();
	}


	void CreateVS() {

		VertexShaderManager::GetInstance()->Create(
			"CSO/VertexShader.cso",
			ConstShader::VSType::NORMAL,
			ConstShader::InputLayout::InputType::VER_COL
		);

		VertexShaderManager::GetInstance()->Create(
			"CSO/VS3D.cso",
			ConstShader::VSType::VS3D,
			ConstShader::InputLayout::InputType::VER_NOR_COL
		);

		VertexShaderManager::GetInstance()->Create(
			"CSO/VS2D.cso",
			ConstShader::VSType::VS2D,
			ConstShader::InputLayout::InputType::VER_COL
		);


		VertexShaderManager::GetInstance()->Create(
			"CSO/LightVertexShader.cso",
			ConstShader::VSType::VARIOUS_LIGHT,
			ConstShader::InputLayout::InputType::VER_NOR_COL
		);


	}


	void InitConstVS() {


		// 定数バッファを使えるようにする
		// なし
		//VertexShaderManager::GetInstance()->GetPtr(
		//	ConstShader::VSType::NORMAL)->
		//	CreateConstBuffer(0,0);


		VertexShaderManager::GetInstance()->GetPtr(
			ConstShader::VSType::VS3D)->
			CreateConstBuffer(0,sizeof(TS3DMatrixData));


		VertexShaderManager::GetInstance()->
			GetPtr(ConstShader::VSType::VARIOUS_LIGHT)->
			CreateConstBuffer(0,sizeof(LightConstBuffer));

		VertexShaderManager::GetInstance()->
			GetPtr(ConstShader::VSType::VS2D)->
			CreateConstBuffer(0, sizeof(VS2DData));

	}


	void CreatePS() {

		PixelShaderManager::GetInstance()->Create(
			"CSO/PixelShader.cso",
			ConstShader::PSType::NORMAL
		);


		PixelShaderManager::GetInstance()->Create(
			"CSO/LightPixelShader.cso",
			ConstShader::PSType::VARIOUS_LIGHT
		);

	}


	void InitConstPS() {

		//// なし
		//if (PixelShaderManager::GetInstance()->GetPtr(
		//	ConstShader::PSType::NORMAL
		//)->CreateConstBuffer(
		//	0,
		//	0
		//) == false) {
		//	return;
		//}


		if (PixelShaderManager::GetInstance()->GetPtr(
			ConstShader::PSType::VARIOUS_LIGHT)
			->CreateConstBuffer(
				0,
				sizeof(LightConstBuffer)
			) == false) {
			return;
		}
	}

}