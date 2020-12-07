#include"CreateShader.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"
#include"../Shader/ConstantShader/ConstantShader.h"
#include"../TransformMatrixData3D/TransformMatrixData3D.h"
#include"../LightConstBuffer/LightConstBuffer.h"



namespace CreateShader {


	void Create() {

		CreateVS();
		InitVS();

		CreatePS();
		InitPS();
	}


	void CreateVS() {

		VertexShaderManager::GetInstance()->Create(
			"Lib/Shader/CSO/VertexShader.cso",
			ConstantShader::VSType::NORMAL
		);

		VertexShaderManager::GetInstance()->Create(
			"Lib/Shader/CSO/VS3D.cso",
			ConstantShader::VSType::VS3D
		);

		VertexShaderManager::GetInstance()->Create(
			"Lib/Shader/CSO/LightVertexShader.cso",
			ConstantShader::VSType::VARIOUS_LIGHT
		);
	}


	void InitVS() {


		// 定数バッファを使えるようにする
		// なし
		VertexShaderManager::GetInstance()->GetPtr(ConstantShader::VSType::NORMAL)
			->GetConstBuffer()->Init(
			Device::GetInstance()->GetPtrDevice(),
			sizeof(NULL),
			D3D11_BIND_CONSTANT_BUFFER
		);


		VertexShaderManager::GetInstance()->GetPtr(ConstantShader::VSType::VS3D)
			->GetConstBuffer()->Init(
			Device::GetInstance()->GetPtrDevice(),
			sizeof(TS3DMatrixData),
			D3D11_BIND_CONSTANT_BUFFER
		);


		VertexShaderManager::GetInstance()->
			GetPtr(ConstantShader::VSType::VARIOUS_LIGHT)
			->GetConstBuffer()->Init(
				Device::GetInstance()->GetPtrDevice(),
				sizeof(LightConstBuffer),
				D3D11_BIND_CONSTANT_BUFFER
		);

	}

	void CreatePS() {

		PixelShaderManager::GetInstance()->Create(
			"Lib/Shader/CSO/PixelShader.cso",
			ConstantShader::PSType::NORMAL
		);


		PixelShaderManager::GetInstance()->Create(
			"Lib/Shader/CSO/LightPixelShader.cso",
			ConstantShader::PSType::VARIOUS_LIGHT
		);

	}



	void InitPS() {

		// なし
		PixelShaderManager::GetInstance()->GetPtr(
			ConstantShader::PSType::NORMAL
		)->GetConstBuffer()->Init(
			Device::GetInstance()->GetPtrDevice(),
			sizeof(NULL),
			D3D11_BIND_CONSTANT_BUFFER
		);


		PixelShaderManager::GetInstance()->GetPtr(ConstantShader::PSType::VARIOUS_LIGHT)
			->GetConstBuffer()->Init(
				Device::GetInstance()->GetPtrDevice(),
				sizeof(LightConstBuffer),
				D3D11_BIND_CONSTANT_BUFFER
			);
	}

}