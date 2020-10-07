#include"Lib.h"
#include"../Input/Key/Key.h"
#include"../Input/GamePad/GamePad.h"



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

	// シングルトン作成
	Singleton<Device>::CreateInstance();

	Singleton<Device>::GetInstance()->Init(
		mp_window->GetWindowName()
	);

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
	Singleton<Device>::GetInstance()->Release();

	// インスタンスを解放
	Singleton<Device>::DestroyInstance();
}