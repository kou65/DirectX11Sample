#include"LibSingletonManager.h"
#include"../Device/Device.h"
#include"../PrimitiveRenderer/PrimitiveRenderer.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"


void LibSingletonManager::Create() {

	// 各シングルトン作成
	Device::CreateInstance();
	VertexShaderManager::CreateInstance();
	PixelShaderManager::CreateInstance();
	PrimitiveRenderer::CreateInstance();
}


void LibSingletonManager::Destroy() {

	// 各インスタンス解放
	Device::DestroyInstance();
	VertexShaderManager::DestroyInstance();
	PixelShaderManager::DestroyInstance();
	PrimitiveRenderer::DestroyInstance();
}