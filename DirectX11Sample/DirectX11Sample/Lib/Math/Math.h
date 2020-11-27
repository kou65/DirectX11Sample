#ifndef MATH_H_
#define MATH_H_

#include<d3d11.h>
#include<math.h>
#include<DirectXMath.h>


using namespace DirectX;


/**
* @namespace Math
*/
namespace Math {


	const float PI = 3.141592653589793238462643383279f;

	/**
	* @brief ラジアン(1.f ~ 0.f)変換
	*/
	float DegreesToRad(
		float degrees
	);


	/**
	* @brief ディグリー(角)変換
	*/
	float RadToDegrees(
		float radian
	);



	float GetLength(const XMFLOAT3& point);


	float GetLength(const XMFLOAT2& point);


	XMFLOAT3 GetDirVec1(
		const XMFLOAT3& vec1,
		const XMFLOAT3& vec2);


	XMFLOAT3 CalcNormalize(const XMFLOAT3& vec1);


	void Rotation2D(
		float radian,
		const float& cx,
		const float& cy,
		float &x,
		float &y
	);

	void Rotation2D2(
		float radian,
		float& x,
		float& y
	);

	namespace TS_XMFLOAT4X4 {


		/**
		* @brief 代入
		*/
		void SubXMFLOAT4X4(
			XMFLOAT4X4* out,
			const XMFLOAT4X4& mat
		);


		/**
		* @brief 等しいかどうか
		*/
		bool IsXMFLOAT4X4Match(
			const XMFLOAT4X4& m1,
			const XMFLOAT4X4& m2
		);

		/**
		* @brief 行列を全て0にする
		*/
		void ClearXMFLOAT4X4(
			XMFLOAT4X4*out
		);


		/**
		* @brief 掛け合わせ行列
		*/
		void MultipleXMFLOAT4X4(
		XMFLOAT4X4*out,
			XMFLOAT4X4&mat1,
			XMFLOAT4X4&mat2
		);

		/**
		* @brief 調整中の掛け合わせ行列
		*/
		void TestMultipleXMFLOAT4X4(
			XMFLOAT4X4* out,
			XMFLOAT4X4& mat1,
			XMFLOAT4X4& mat2
		);

		/**
		* @brief 掃き出し法を用いた逆行列変換
		*/
		void InverseMatrixSweepingMethod(
			XMFLOAT4X4* out,
			XMFLOAT4X4&in
		);


		/**
		* @brief 転置行列
		*/
		void TransposeXMFLOAT4X4(
			XMFLOAT4X4* out
		);


		/**
		* @brief 転置行列2
		*/
		XMFLOAT4X4 TransposeXMFLOAT4X4(
			XMFLOAT4X4& out
		);


		/**
		* @brief 単位行列化
		*/
		void IdentityMatrix(
			XMFLOAT4X4* out
		);


		// アフィン変換
		/*
		float        sx, _12, _13, _14;
		float        _21, sy, _23, _24;
		float        _31, _32, _sz, _34;
		float        tx, ty, tz, _44;
		*/

		/**
		* @brief ワールド座標変換行列
		*/
		void TSMatrixTranslation(
			XMFLOAT4X4* out_mat,
			const XMFLOAT3& trans
		);


		/**
		* @brief 拡縮変換行列
		*/
		void TSMatrixScale(
			XMFLOAT4X4* out_mat,
			const XMFLOAT3& mat
		);


		/**
		* @brief X軸回転行列
		*/
		void TSMatrixRotationX(
			XMFLOAT4X4* out_mat,
			const float& radian
		);


		/**
		* @brief ディグリー版
		*/
		void TSMatrixRotationXDegrees(
			XMFLOAT4X4* out_mat,
			const float& degrees
		);

		/**
		* @brief Y軸回転行列
		*/
		void TSMatrixRotationY(
			XMFLOAT4X4* out_mat,
			const float& radian
		);


		/**
		* @brief Y軸回転行列
		*/
		void TSMatrixRotationYDegrees(
			XMFLOAT4X4* out_mat,
			const float&degrees
		);

		/**
		* @brief Z軸回転行列
		*/
		void TSMatrixRotationZ(
			XMFLOAT4X4* out_mat,
			const float& radian
		);

		void TSMatrixRotationZDegrees(
			XMFLOAT4X4* out_mat,
			const float& degrees
		);


		/**
		* @brief スケール回転移動行列計算
		*/
		void TsSRTRotationZYXMatrix(
			XMFLOAT4X4* out_mat,
			const XMFLOAT3& pos,
			const XMFLOAT3& rotation,
			const XMFLOAT3& scale
		);


		/**
		* @brief カメラ座標の逆行列
		*/
		void TSInverseViewMatrix(
			XMFLOAT4X4* out,
			XMFLOAT4X4& in
		);


		/**
		* @brief ビュー変換行列
		*/
		void TSViewMatrix(
			XMFLOAT4X4* out_mat,
			XMFLOAT3& pos,
			XMFLOAT3& look,
			XMFLOAT3& up_dir_vec
		);


		/**
		* @brief プロジェクション変換行列
		*/
		void TSProjectionMatrix(
			XMFLOAT4X4* out,
			float angle,
			float aspact,
			float _far,
			float _near
		);


		/**
		* @brief スクリーン変換行列
		*/
		void TSScreenMatrix(
			XMFLOAT4X4* out,
			float width,
			float height
		);
	}

	namespace ConvertVec {

		void XMVECTORToXMFLOAT2(
			XMFLOAT2* out_float2,
			XMVECTOR& vec
		);
		void XMVECTORToXMFLOAT3(
			XMFLOAT3* out_floa3,
			XMVECTOR& vec
		);
		void XMVECTORToXMFLOAT4(
			XMFLOAT4* out_float4,
			XMVECTOR& vec
		);

		void XMFLOAT2ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT2& float2
		);
		void XMFLOAT3ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT3& float3
		);
		void XMFLOAT4ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT4& float4
		);
	}


	namespace ConvertMat {
		void XMFLOAT4X4ToXMMATRIX(
			XMMATRIX* out_mat,
			const XMFLOAT4X4& load_mat
		);

		void XMMATRIXToXMFLOAT4X4(
			XMFLOAT4X4* out_float4x4,
			const XMMATRIX& store_mat
		);
	}


	namespace TSMatMultVec {
		/**
		* @brief Mat * Vec = Vec2 変換
		*/
		void TSXMVector2(
			XMVECTOR* out_vec,
			const XMVECTOR& vec,
			const XMMATRIX& mat
		);

		void TSXMVector3(
			XMVECTOR* out_vec,
			const XMVECTOR& vec,
			const XMMATRIX& mat
		);

		void TSXMVector4(
			XMVECTOR* out_vec,
			const XMVECTOR& vec,
			const XMMATRIX& mat
		);
	}


	namespace Dot {
		/**
		* @brief 内積計算　普通に行えばスカラー値が返ってくる
		* @brief その他にどちらかを単位かすればcos値が取り出せる
		*/
		void DotXMFLOAT3(
			float* out_vec,
			XMFLOAT3& vec1,
			XMFLOAT3& vec2
		);


		/**
		* @brief 垂直チェックと正と負チェック
		* @return 垂直 = 0 正 = 1 負 = -1 エラー = -2
		*/
		int CheckDot(
			XMFLOAT3& vec1,
			XMFLOAT3& vec2
		);
	}


	namespace Cross {


		void CrossXMFLOAT3(
			XMFLOAT3* out,
			const XMFLOAT3& vec1,
			const XMFLOAT3& vec2
		);
	}
}

#endif
