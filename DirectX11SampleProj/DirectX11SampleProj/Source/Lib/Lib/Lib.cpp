#include"Lib.h"
#include"../Input/Key/Key.h"
#include"../Input/GamePad/GamePad.h"
#include"../LibSingletonManager/LibSingletonManager.h"
#include"../PrimitiveRenderer/PrimitiveRenderer.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"
#include"../CreateShader/CreateShader.h"



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
	Device::GetInstance()->Create(
		mp_window->GetWindowName()
	);

	// シェーダーファイルを各管理者に生成させる
	CreateShader::Create();

	// レンダラーの初期化
	PrimitiveRenderer::GetInstance()->Create();

	return true;
}


bool Lib::Update() {

	Key::GetInterface().Update();

	// インデックス1のコントローラ更新
	Gamepad<0>::getInterface().update();

	return true;
}


void Lib::Release() {

	// シェーダーファイル全て解放
	VertexShaderManager::GetInstance()->DestroyEverything();
	PixelShaderManager::GetInstance()->DestroyEverything();

	// 解放
	Device::GetInstance()->DestroyEverything();

	// ライブラリ用のシングルトンを作成
	LibSingletonManager::GetInstance()->DestroyEverything();
}