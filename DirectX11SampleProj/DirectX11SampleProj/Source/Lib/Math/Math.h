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


	//! 円周率
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


	/**
	* @brief 距離取得
	*/
	float GetLength(const XMFLOAT3& point);


	/**
	* @brief 距離取得
	*/
	float GetLength(const XMFLOAT2& point);


	/**
	* @brief ベクター2からベクター1への方向ベクトルを受け取る
	*/
	XMFLOAT3 GetDirVec1(
		const XMFLOAT3& vec1,
		const XMFLOAT3& vec2);


	/**
	* @brief 正規化
	*/
	XMFLOAT3 CalcNormalize(const XMFLOAT3& vec1);


	/**
	* @param[in] radian ラジアン
	* @param[in] x 原点x
	* @param[in] y 原点y
	*/
	void Rotation2D(
		float radian,
		const float& cx,
		const float& cy,
		float &x,
		float &y
	);


	/**
	* @param[in] radian ラジアン
	* @param[in] x 現在位置x
	* @param[in] y 現在位置y
	*/
	void Rotation2D2(
		float radian,
		float& x,
		float& y
	);


	/**
	* @brief 2D変換射影行列作成
	*/
	XMMATRIX Calc2DProj(
		const float window_width = 1920.f,
		const float window_height = 1080.f
	);



	/**
	* @brief XMMATRIX行列変換
	*/
	namespace TSXMMATRIX {


		/**
		* @brief 単位ベクトル化
		*/
		inline XMMATRIX Identity() {

			return XMMatrixIdentity();
		}


	}


	namespace TSXMfloat4x4 {


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


		/**
		* @brief Z回転値
		*/
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
		//void TSInverseViewMatrix(
		//	XMFLOAT4X4* out,
		//	XMFLOAT4X4& in
		//);


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

		inline void XMVECTORToXMFLOAT2(
			XMFLOAT2* out_float2,
			XMVECTOR& vec
		) {
			XMStoreFloat2(out_float2, vec);
		}


		inline void XMVECTORToXMFLOAT3(
			XMFLOAT3* out_float3,
			XMVECTOR& vec
		) {

			XMStoreFloat3(out_float3, vec);
		}


		inline void XMVECTORToXMFLOAT4(
			XMFLOAT4* out_float4,
			XMVECTOR& vec
		) {

			XMStoreFloat4(out_float4, vec);
		}


		inline void XMFLOAT2ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT2& float2
		) {

			*out_vec =
				XMLoadFloat2(&float2);
		}
		

		inline void XMFLOAT3ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT3& float3
		) {

			*out_vec =
				XMLoadFloat3(&float3);
		}



		inline void XMFLOAT4ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT4& float4
		) {

			*out_vec =
				XMLoadFloat4(&float4);
		}
	}


	namespace ConvertMat {
		
		inline void XMFLOAT4X4ToXMMATRIX(
			XMMATRIX* out_mat,
			const XMFLOAT4X4& load_mat
		) {

			// XMMATRIXへの変換
			*out_mat = XMLoadFloat4x4(
				&load_mat
			);
		}

		inline void XMMATRIXToXMFLOAT4X4(
			XMFLOAT4X4* out,
			const XMMATRIX& store_mat
		) {

			// XMMATRIXから値を取り出す
			XMStoreFloat4x4(out, store_mat);
		}
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

		inline void DotXMFLOAT3(
			float* out_vec,
			XMFLOAT3& vec1,
			XMFLOAT3& vec2
		) {

			*out_vec
				=
				(vec1.x * vec2.x) +
				(vec1.y * vec2.y) +
				(vec1.z * vec2.z);
		}


		/**
		* @brief 垂直チェックと正と負チェック
		* @return 垂直 = 0 正 = 1 負 = -1 エラー = -2
		*/
		inline int CheckDot(
			XMFLOAT3& vec1,
			XMFLOAT3& vec2
		) {

			/*
			物体とカメラの位置
			物体からカメラの位置を引くと
			物体までのベクトルが割り出せる

			*/

			/*
			なす角
			0° <= θ <= 180°

			*/

			float is = 0.f;
			DotXMFLOAT3(&is, vec1, vec2);

			// 垂直
			if (is == 0.f) {
				return 0;
			}

			// 負の時 θ>90°
			if (is < 0.f) {
				return -1;
			}

			// 正の時 θ<90°
			if (is > 0.f) {
				return 1;
			}

			return -2;
		}
	}


	namespace Cross {


		/**
		* @brief 外積
		*/
		inline void CrossXMFLOAT3(
			XMFLOAT3* out,
			const XMFLOAT3& vec1,
			const XMFLOAT3& vec2
		) {

			// 外積の計算
			out->x = vec1.y * vec2.z - vec1.z * vec2.y;
			out->y = vec1.z * vec2.x - vec1.x * vec2.z;
			out->z = vec1.x * vec2.y - vec1.y * vec2.x;

		}
	}
}

#endif
