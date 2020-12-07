#include"Light.h"
#include"../Shader/VertexShaderManager/VertexShaderManager.h"
#include"../Shader/PixelShaderManager/PixelShaderManager.h"
#include"../Shader/ConstantShader/ConstantShader.h"
#include"../LightConstBuffer/LightConstBuffer.h"
#include"../TransformMatrixData3D/TransformMatrixData3D.h"


void Light::SetParameter(
	Camera3D*p_camera,
	const TS3DMatrixData&ts_data
	) {

	// カメラ位置セット
	m_light_data.CameraPos =
		XMFLOAT4(
			p_camera->GetPos().x, 
			p_camera->GetPos().y,
			p_camera->GetPos().z,
			1.f
		);

	// 変換行列
	m_light_data.World = ts_data.world;
	m_light_data.View = ts_data.view;
	m_light_data.Projection = ts_data.projection;
	m_light_data.LightColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);


	// ライト方向
	DirectX::XMVECTOR light = 
		DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.f, -1.0f, 0.0f, 0.0f));
	XMStoreFloat4(&m_light_data.LightVector, light);

	m_light_data.LightPos = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	m_light_data.MaterialAmbient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f);
	m_light_data.MaterialDiffuse = XMFLOAT4(0.5f, 0.7f, 0.5, 1.f);
	m_light_data.MaterialSpecular = XMFLOAT4(0.7f, 0.5f, 0.5f, 1.f);

	// リソースデータを受け取る
	Device::GetInstance()->GetPtrImmContext()->
		UpdateSubresource(
			VertexShaderManager::GetInstance()->
			GetPtr(ConstantShader::VSType::VARIOUS_LIGHT)
			->GetConstBuffer()->GetBuffer(),
			0,
			NULL,
			&m_light_data,
			0,
			0
		);

	// リソースデータを受け取る
	Device::GetInstance()->GetPtrImmContext()->
		UpdateSubresource(
			PixelShaderManager::GetInstance()->
			GetPtr(ConstantShader::PSType::VARIOUS_LIGHT)
			->GetConstBuffer()->GetBuffer(),
			0,
			NULL,
			&m_light_data,
			0,
			0
		);

}
