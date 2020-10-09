

#include"../WindowsSystem/WindowsSystem.h"
#include"../Lib/Lib.h"
#include"../Input/Mouse/Mouse.h"
#include"../Input/Key/Key.h"
#include"../Math/Math.h"



int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int) 
{

	Lib lib;

	lib.Init();

	while(WindowsSystem::ProcessMessage() == true) {

		// 更新
		lib.Update();

		XMFLOAT4X4 mat,trans,scale;
		Math::TS_XMFLOAT4X4::IdentityMatrix(&mat);
		Math::TS_XMFLOAT4X4::IdentityMatrix(&trans);
		Math::TS_XMFLOAT4X4::IdentityMatrix(&scale);

		XMFLOAT3 vec;
		vec.x = 200.f;
		vec.y = 10.f;
		vec.z = 256.f;

		Math::TS_XMFLOAT4X4::TSMatrixTranslation(&trans,vec);

		vec.x = 3.f;
		vec.y = 3.f;
		vec.z = 2.f;

		Math::TS_XMFLOAT4X4::TSMatrixScale(&scale, vec);


		Math::TS_XMFLOAT4X4::MultipleXMFLOAT4X4(&mat,scale,trans);


		// 描画開始
		Singleton<Device>::GetInstance()->StartRendering();


		// 描画終了
		Singleton<Device>::GetInstance()->EndRendering();
	}

	lib.Release();

	return 0;
}