#include"LibSingletonManager.h"
#include"../Device/Device.h"
#include"../PrimitiveRenderer/PrimitiveRenderer.h"


void LibSingletonManager::Create() {

	// 各シングルトン作成
	Device::CreateInstance();
	PrimitiveRenderer::CreateInstance();
}


void LibSingletonManager::Destory() {

	// インスタンス解放
	Device::DestroyInstance();
	PrimitiveRenderer::DestroyInstance();
}