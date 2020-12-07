

#include"../WindowsSystem/WindowsSystem.h"
#include"../Lib/Lib.h"
#include"../Input/Mouse/Mouse.h"
#include"../Input/Key/Key.h"
#include"../Math/Math.h"
#include"../Device/Device.h"
#include"../PrimitiveRenderer/PrimitiveRenderer.h"
#include"../Polygon/Surface2D/Surface2D.h"
#include"../Polygon/Triangle/Triangle.h"
#include"../Polygon/Cube/Cube.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/ConstantShader/ConstantShader.h"
#include"../Camera3D/Camera3D.h"
#include"../Light/Light.h"



void TestMath();

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int) 
{

	Lib lib;

	lib.Init();

	Camera3D camera;

	Surface2D s;

	Light light;

	s.Create(
		Device::GetInstance(),
		VertexShaderManager::GetInstance()->GetPtr(
		ConstantShader::VSType::NORMAL
		)
	);


	Triangle t;
	t.Create(
		Device::GetInstance()->GetPtrDevice(),
		VertexShaderManager::GetInstance()->GetPtr(
			ConstantShader::VSType::NORMAL
		)
	);


	Cube cube(&camera);

	cube.Create(
		Device::GetInstance()->GetPtrDevice(),
		VertexShaderManager::GetInstance()->GetPtr(
			ConstantShader::VSType::VS3D
		)
	);


	while(WindowsSystem::ProcessMessage() == true) {

		if (Key::GetInterface().Push(VK_ESCAPE) == true) {
			break;
		}

		// 更新
		lib.Update();

		// カメラの更新
		camera.Update();

		// キューブ更新
		cube.Update(
			VertexShaderManager::GetInstance()->GetPtr(
				ConstantShader::VSType::VS3D
			)
		);

		// ライトパラメータ
		light.SetParameter(
			&camera,
			cube.GetTSMatrix()
		);

		// 回転
		{
			if (Key::GetInterface().Pushing(VK_LEFT)) {
				camera.AddDegree(XMFLOAT3(0.f, -0.01f, 0.f));
			}

			if (Key::GetInterface().Pushing(VK_RIGHT)) {
				camera.AddDegree(XMFLOAT3(0.f, 0.01f, 0.f));
			}

			if (Key::GetInterface().Pushing(VK_UP)) {
				camera.AddDegree(XMFLOAT3(0.01f, 0.f, 0.f));
			}

			if (Key::GetInterface().Pushing(VK_DOWN)) {
				camera.AddDegree(XMFLOAT3(-0.01f, 0.f, 0.f));
			}
		}

		// 移動
		{
			if (Key::GetInterface().Pushing('D')) {
				camera.AddPos(XMFLOAT3(0.001f, 0.f, 0.f));
			}
			if (Key::GetInterface().Pushing('A')) {
				camera.AddPos(XMFLOAT3(-0.001f, 0.f, 0.f));
			}
			if (Key::GetInterface().Pushing('W')) {
				camera.AddPos(XMFLOAT3(0.f, 0.f, 0.001f));
			}
			if (Key::GetInterface().Pushing('S')) {
				camera.AddPos(XMFLOAT3(0.f, 0.f, -0.001f));
			}
		}

		// 描画開始
		Device::GetInstance()->StartRendering();

		
		//PrimitiveRenderer::GetInstance()->
		//	RenderingPolygonByDeviceView(&t,
		//		ConstantShader::VSType::NORMAL,
		//		ConstantShader::PSType::NORMAL
		//	);

		//PrimitiveRenderer::
		//	GetInstance()->RenderingMeshByDeviceView(
		//	&s
		//);
		

		PrimitiveRenderer::GetInstance()->RenderingMeshByDeviceView(
			&cube,
			ConstantShader::VSType::VARIOUS_LIGHT,
			ConstantShader::PSType::VARIOUS_LIGHT
		);

		// 描画終了
		Device::GetInstance()->EndRendering();
	}

	lib.Release();

	return 0;
}




void TestMath() {



	{
		float px = 10.f, py = 10.f, r = 0.f, out_x = 0.f, out_y = 0.f;

		Math::Rotation2D(
			Math::DegreesToRad(r),
			px,     // ここから回す位置(原点ではない)
			py,     // ここから回す位置
			out_x,	// 参照値
			out_y	// 参照値
		);


		Math::Rotation2D2(
			Math::DegreesToRad(r),
			px,
			py
		);


		XMFLOAT4X4 mat, trans, scale;
		Math::TS_XMFLOAT4X4::IdentityMatrix(&mat);
		Math::TS_XMFLOAT4X4::IdentityMatrix(&trans);
		Math::TS_XMFLOAT4X4::IdentityMatrix(&scale);

		XMFLOAT3 vec;
		vec.x = 200.f;
		vec.y = 10.f;
		vec.z = 256.f;

		Math::TS_XMFLOAT4X4::TSMatrixTranslation(&trans, vec);

		vec.x = 3.f;
		vec.y = 3.f;
		vec.z = 2.f;

		Math::TS_XMFLOAT4X4::TSMatrixScale(&scale, vec);


		Math::TS_XMFLOAT4X4::MultipleXMFLOAT4X4(&mat, scale, trans);
	}

}
