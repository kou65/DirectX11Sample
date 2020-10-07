#include"Math.h"




namespace Math {


	float DegreesToRad(
		float degree
	) {
		return (degree * PI / 180.f);
	}


	float RadToDegrees(
		float radian
	) {
		return (radian * 180.f / PI);
	}


	float GetLength(const XMFLOAT3& dir) {

		// 三平方の定理で距離を出す
		// 平方根化
		return(sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z)));
	}


	XMFLOAT3 GetDirVec1(const XMFLOAT3& vec1, const XMFLOAT3& vec2) {

		XMFLOAT3 out_vec;
		// 方向割り出し
		out_vec.x = vec1.x - vec2.x;
		out_vec.y = vec1.y - vec2.y;
		out_vec.z = vec1.z - vec2.z;

		return out_vec;
	}


	XMFLOAT3 CalcNormalize(const XMFLOAT3& vec1) {

		XMFLOAT3 XMFLOAT3;

		// 単位ベクトル化(1)にし、回転値など受け取る
		XMFLOAT3.x = vec1.x / GetLength(vec1);
		XMFLOAT3.y = vec1.y / GetLength(vec1);
		XMFLOAT3.z = vec1.z / GetLength(vec1);

		return XMFLOAT3;
	}


}


namespace Math {


	namespace TS_XMFLOAT4X4 {


		void SubXMFLOAT4X4(
			XMFLOAT4X4* out,
			const XMFLOAT4X4& mat
		) {

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					out->m[i][j] = mat.m[i][j];
				}
			}
		}

		bool IsXMFLOAT4X4Match(
			const XMFLOAT4X4& m1,
			const XMFLOAT4X4& m2
		) {

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (m1.m[i][j] != m2.m[i][j]) {
						return false;
					}
				}
			}

			return true;
		}


		void TransposeXMFLOAT4X4(
			XMFLOAT4X4* out
		) {


			/*
			転置図

			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

			 ↓

			float        _11, _21, _31, _41;
			float        _12, _22, _32, _42;
			float        _13, _23, _33, _43;
			float        _14, _24, _34, _44;

			*/

			float temp;
			// 転置

			// 行と列を入れ替える

			// 1行1列目
			temp =
				out->_21;
			out->_21 = out->_12;
			out->_12 = temp;

			temp = out->_31;
			out->_31 = out->_13;
			out->_13 = temp;

			temp = out->_41;
			out->_41 = out->_14;
			out->_14 = temp;


			// 一つずらして2行2列目
			temp = 
				out->_32;
			out->_32 = out->_23;
			out->_23 = temp;

			temp = out->_42;
			out->_42 = out->_24;
			out->_24 = temp;

			temp = out->_43;
			out->_43 = out->_34;
			out->_34 = temp;

		}

		XMFLOAT4X4 TransposeXMFLOAT4X4(
			XMFLOAT4X4& out
		) {

			XMFLOAT4X4 temp;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					temp.m[i][j]
						= out.m[j][i];
				}
			}

			return temp;
		}


		void IdentityMatrix(
			XMFLOAT4X4* out
		) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {

					out->m[i][j] = 0;
				}
			}

			out->_11 = 1.f;
			out->_22 = 1.f;
			out->_33 = 1.f;
			out->_44 = 1.f;
		}

		void MultipleXMFLOAT4X4(
			XMFLOAT4X4* out,
			XMFLOAT4X4& mat1,
			XMFLOAT4X4& mat2
		) {

			// (行1 * 列1) + (行1 * 列2) + (行1 * 列3) + (行1 * 列4)
			// (行2 * 列1) + (行2 * 列2) + (行2 * 列3) + (行2 * 列4)
			// (行3 * 列1) + (行3 * 列2) + (行3 * 列3) + (行3 * 列4)
			// (行4 * 列1) + (行4 * 列2) + (行4 * 列3) + (行4 * 列4)

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {

						// (i行 * k列i行) * 4
						out->m[i][j]
							+=
							
							// 行
							mat1.m[i][k] *
							mat2.m[k][i];
					}
				}
			}
			
		}


		void TSMatrixTranslation(
			XMFLOAT4X4* out_mat,
			XMFLOAT3& trans
		) {

			out_mat->_41 = trans.x;
			out_mat->_42 = trans.y;
			out_mat->_43 = trans.z;
		}


		void TSMatrixScailing(
			XMFLOAT4X4* out_mat,
			XMFLOAT3& float3
		) {
			out_mat->_11 = float3.x;
			out_mat->_22 = float3.y;
			out_mat->_33 = float3.z;
		}


		/*

		左手系と右手系の違い
		Z軸が逆向き
		X軸とY軸の回転が逆

		行列の利点
		移動や回転を乗算することで
		組み合わせて変換できる利点があるから


		*/


		void TSMatrixRotationX(
			XMFLOAT4X4* out_mat,
			float& radian
		) {

			// x軸 ピッチ
			out_mat->_22 = cosf(radian);
			out_mat->_23 = -1 * sinf(radian);
			out_mat->_32 = sinf(radian);
			out_mat->_33 = cosf(radian);

			out_mat->_11 = 1.f;
			out_mat->_44 = 1.f;
		}


		void TSMatrixRotationY(
			XMFLOAT4X4* out_mat,
			float& radian
		) {

			// ヨー
			out_mat->_11 = cosf(radian);
			out_mat->_13 = sinf(radian);
			out_mat->_31 = -1.f * sinf(radian);
			out_mat->_33 = cosf(radian);

			out_mat->_22 = 1.f;
			out_mat->_44 = 1.f;

		}

		void TSMatrixRotationZ(
			XMFLOAT4X4* out_mat,
			float& radian
		) {

			// z軸 ロール
			out_mat->_11 = cosf(radian);
			out_mat->_12 = -1 * sinf(radian);
			out_mat->_21 = sinf(radian);
			out_mat->_22 = cosf(radian);

			out_mat->_33 = 1;
			out_mat->_44 = 1;

		}

		void TSMatrixRotationXDegrees(
			XMFLOAT4X4* out_mat,
			float& degrees
		) {
			TSMatrixRotationX(
				out_mat,
				DegreesToRad(degrees)
			);
		}

		void TSMatrixRotationYDegrees(
			XMFLOAT4X4* out_mat,
			float& degrees
		) {
			TSMatrixRotationY(
				out_mat,
				DegreesToRad(degrees)
			);
		}

		void TSMatrixRotationZDegrees(
			XMFLOAT4X4* out_mat,
			float& degrees
		) {
			

			TSMatrixRotationZ(
				out_mat,
				DegreesToRad(degrees)
			);
		}


		void TSViewMatrix(
			XMFLOAT4X4*out_mat,
			XMFLOAT3& pos,
			XMFLOAT3& look,
			XMFLOAT3& up_dir_vec
		) {

			XMFLOAT3 z_axis;

			// カメラの視点位置からカメラ位置を引く
			// AToBベクトル取得
			z_axis.x = look.x - pos.x;
			z_axis.y = look.y - pos.y;
			z_axis.z = look.z - pos.z;

			// z軸
			// 単位ベクトル化
			CalcNormalize(z_axis);

			XMFLOAT3 x_axis;

			// x軸
			// 外積の結果は直行しているベクトルになる
			Cross::CrossXMFLOAT3(
				&x_axis,
				up_dir_vec,
				z_axis
			);

			// 単位ベクトル化
			CalcNormalize(x_axis);

			// y軸
			XMFLOAT3 y_axis;

			// x軸とz軸でy軸を算出
			// 上方向ベクトルは直行しているかどうか不明
			// xyz軸を垂直に交わらせる必要がある

			Cross::CrossXMFLOAT3(
				&y_axis,
				z_axis,
				x_axis
			);

			// 単位ベクトル化
			CalcNormalize(y_axis);
		}
	}

}


namespace Math {

	namespace TSMatMultVec {
		void TSXMVector2(
			XMVECTOR* out_vec,
			const XMVECTOR& vec,
			const XMMATRIX& mat
		) {

			*out_vec = XMVector2Transform(vec, mat);
		}

		void TSXMVector3(
			XMVECTOR* out_vec,
			const XMVECTOR& vec,
			const XMMATRIX& mat
		) {
			*out_vec = XMVector3Transform(vec, mat);
		}

		void TSXMVector4(
			XMVECTOR* out_vec,
			const XMVECTOR& vec,
			const XMMATRIX& mat
		) {
			*out_vec = XMVector4Transform(vec, mat);
		}
	}
}

namespace Math {


	namespace ConvertVec {

		void XMVECTORToXMFLOAT2(
			XMFLOAT2* out_float2,
			XMVECTOR& vec
		) {
			XMStoreFloat2(out_float2, vec);
		}
		void XMVECTORToXMFLOAT3(
			XMFLOAT3* out_float3,
			XMVECTOR& vec
		) {

			XMStoreFloat3(out_float3, vec);
		}
		void XMVECTORToXMFLOAT4(
			XMFLOAT4* out_float4,
			XMVECTOR& vec
		) {

			XMStoreFloat4(out_float4, vec);
		}

		void XMFLOAT2ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT2& float2
		) {

			*out_vec =
				XMLoadFloat2(&float2);
		}
		void XMFLOAT3ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT3& float3
		) {

			*out_vec =
				XMLoadFloat3(&float3);
		}
		void XMFLOAT4ToXMVECTOR(
			XMVECTOR* out_vec,
			XMFLOAT4& float4
		) {

			*out_vec =
				XMLoadFloat4(&float4);
		}
	}
}

namespace Math {

	namespace ConvertMat {

		void XMFLOAT4X4ToXMMATRIX(
			XMMATRIX* out_mat,
			const XMFLOAT4X4& load_mat
		) {

			// XMMATRIXへの変換
			*out_mat = XMLoadFloat4x4(
				&load_mat
			);
		}

		void XMMATRIXToXMFLOAT4X4(
			XMFLOAT4X4* out,
			const XMMATRIX& store_mat
		) {

			// XMMATRIXから値を取り出す
			XMStoreFloat4x4(out, store_mat);
		}
	}
}


namespace Math {


	namespace Dot {

		void DotXMFLOAT3(
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


		int CheckDot(
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
}


namespace Math {

	namespace Cross {


		void CrossXMFLOAT3(
			XMFLOAT3*out,
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