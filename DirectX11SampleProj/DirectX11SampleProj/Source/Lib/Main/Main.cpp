

#include"../WindowsSystem/WindowsSystem.h"
#include"../Lib/Lib.h"
#include"../Input/Mouse/Mouse.h"
#include"../Input/Key/Key.h"
#include"../Math/Math.h"
#include"../Device/Device.h"
#include"../PrimitiveRenderer/PrimitiveRenderer.h"
#include"../Polygon/Quad/Quad.h"
#include"../Polygon/Triangle/Triangle.h"
#include"../Polygon/Cube/Cube.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/ConstShader/ConstShader.h"
#include"../Camera3D/Camera3D.h"
#include"../Light/Light.h"
#include"../OBJ/OBJFile/OBJFile.h"
#include"../Polygon/ModelManager/ModelManager.h"
#include"../ConstBufferData/VS2DData/VS2DData.h"



void TestMath();

void UpdateVS2D();


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int) 
{

	Lib lib;

	lib.Init();

	Camera3D camera;

	Quad s;

	Light light;

	s.Create();


	Triangle t;
	t.Create(
		Device::GetInstance()->GetPtrDevice()
	);


	Cube cube(&camera);

	cube.Create(
		Device::GetInstance()->GetPtrDevice()
	);

	//// モデル読み込み
	//ModelManager::GetInstance()->Load(
	//	ModelManager::FileFormat::OBJ,
	//	"Resource/Sphere/Sphere.obj",
	//	"sphere"
	//);


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
				ConstShader::VSType::VS3D
			)
		);


		UpdateVS2D();

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
		//	RenderingPolygonByDeviceView(&t.GetPolygon(),
		//		ConstShader::VSType::NORMAL,
		//		ConstShader::PSType::NORMAL
		//	);

		

		PrimitiveRenderer::GetInstance()->RenderingMeshByDeviceView(
			&cube.GetMesh(),
			ConstShader::VSType::VARIOUS_LIGHT,
			ConstShader::PSType::VARIOUS_LIGHT
		);

		// VS2Dの定数バッファをセット
		PrimitiveRenderer::GetInstance()->VSSetConstBuffer(
			ConstShader::VSType::VS2D,
			0
		);

		PrimitiveRenderer::GetInstance()->RenderingPolygonByDeviceView(
			&s.GetPolygon(),
			ConstShader::VSType::VS2D,
			ConstShader::PSType::NORMAL
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
		Math::TSXMfloat4x4::IdentityMatrix(&mat);
		Math::TSXMfloat4x4::IdentityMatrix(&trans);
		Math::TSXMfloat4x4::IdentityMatrix(&scale);

		XMFLOAT3 vec;
		vec.x = 200.f;
		vec.y = 10.f;
		vec.z = 256.f;

		Math::TSXMfloat4x4::TSMatrixTranslation(&trans, vec);

		vec.x = 3.f;
		vec.y = 3.f;
		vec.z = 2.f;

		Math::TSXMfloat4x4::TSMatrixScale(&scale, vec);


		Math::TSXMfloat4x4::MultipleXMFLOAT4X4(&mat, scale, trans);
	}

}


void UpdateVS2D() {


	XMMATRIX trans;
	XMMATRIX rotation_x, rotation_y, rotation_z, total_rot;
	XMMATRIX scale;

	float rx = 0.f;
	float ry = 0.f;
	float rz = 0.f;

	float sx = 1900.f;
	float sy = 100.f;
	float sz = 1.f;

	// 移動行列
	trans =
		XMMatrixTranslation(
			rx,
			ry,
			rz
		);

	// 回転行列
	rotation_y = XMMatrixRotationY(Math::DegreesToRad(0));
	rotation_x = XMMatrixRotationX(Math::DegreesToRad(0));
	rotation_z = XMMatrixRotationZ(Math::DegreesToRad(0));

	// 合計回転
	total_rot = rotation_z * rotation_y * rotation_x;

	// 拡縮
	scale = XMMatrixScaling(sx, sy, sz);

	// ワールド座標更新
	XMMATRIX world = XMMatrixTranspose(scale * total_rot * trans);


	// ウィンドウ横幅
	const float WINDOW_WIDTH = 1920.f;

	// ウィンドウ縦幅
	const float WINDOW_HEIGHT = 1080.f;

	// 2D射影変換行列
	XMMATRIX proj =
		XMMatrixTranspose(
			Math::Calc2DProj(
				WINDOW_WIDTH,
				WINDOW_HEIGHT
			)
		);


	VS2DData data;

	Math::ConvertMat::XMMATRIXToXMFLOAT4X4(&data.world,world);
	Math::ConvertMat::XMMATRIXToXMFLOAT4X4(&data.proj,proj);

	// 頂点2D
	ID3D11Buffer*p_vsb =
	VertexShaderManager::GetInstance()->
		GetPtr(ConstShader::VSType::VS2D)->
		GetConstBuffer(0);


	// リソースデータを送る
	Device::GetInstance()->GetPtrImmContext()->
		UpdateSubresource(
			p_vsb,
			0,
			NULL,
			&data,
			0,
			0
		);

}
