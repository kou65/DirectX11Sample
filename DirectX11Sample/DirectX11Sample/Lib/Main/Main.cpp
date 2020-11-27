

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




int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int) 
{

	Lib lib;

	lib.Init();


	Surface2D s;

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

	Cube cube;

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
			ConstantShader::VSType::VS3D,
			ConstantShader::PSType::NORMAL
		);

		// 描画終了
		Device::GetInstance()->EndRendering();
	}

	lib.Release();

	return 0;
}