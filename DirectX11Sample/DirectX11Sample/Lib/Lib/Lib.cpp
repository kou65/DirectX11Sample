#include"Lib.h"
#include"../Input/Key/Key.h"
#include"../Input/GamePad/GamePad.h"
#include"../LibSingletonManager/LibSingletonManager.h"
#include"../PrimitiveRenderer/PrimitiveRenderer.h"



Lib::Lib() {

	mp_window = std::make_unique<Window>(
		"Window1",
		"DirectX11Sample",
		1920,
		1080
		);
}


bool Lib::Init() {

	if (mp_window->Create() == false) {
		return false;
	}

	// ライブライ用シングルトン管理者のインスタンス作成
	LibSingletonManager::CreateInstance();

	// ライブラリ用のシングルトンを作成
	LibSingletonManager::GetInstance()->Create();

	// デバイスの初期化
	Device::GetInstance()->Init(
		mp_window->GetWindowName()
	);

	// レンダラーの初期化
	PrimitiveRenderer::GetInstance()->Init();

	return true;
}


bool Lib::Update() {

	Key::GetInterface().Update();

	// インデックス1のコントローラ更新
	Gamepad<0>::getInterface().update();

	return true;
}


void Lib::Release() {

	// 解放
	//Device::GetInstance()->Release();

	// ライブラリ用のシングルトンを作成
	//LibSingletonManager::GetInstance()->Destory();
}