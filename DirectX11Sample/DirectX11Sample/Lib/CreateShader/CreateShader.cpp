#include"CreateShader.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"
#include"../Shader/ConstantShader/ConstantShader.h"



namespace CreateShader {


	void Create() {

		CreateVS();
		CreatePS();
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
	}

	void CreatePS() {

		PixelShaderManager::GetInstance()->Create(
			"Lib/Shader/CSO/PixelShader.cso",
			ConstantShader::PSType::NORMAL
		);
	}

}