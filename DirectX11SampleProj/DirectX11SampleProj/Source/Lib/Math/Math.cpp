#include"Math.h"




namespace Math {


	float DegreesToRad(
		float degree
	) {
		return (degree * (PI / 180.f));
	}


	float RadToDegrees(
		float radian
	) {
		return (radian * (180.f / PI));
	}


	float GetLength(const XMFLOAT3& p) {

		// 三平方の定理で距離を出す
		// 平方根化
		return(sqrtf((p.x * p.x) + (p.y * p.y) + (p.z * p.z)));
	}


	float GetLength(const XMFLOAT2& p) {

		return sqrtf((p.x * p.x) + (p.y * p.y));
	}


	void Rotation2D(
		float radian,
		const float& cx,
		const float& cy,
		float& x,
		float& y
	) {


		XMFLOAT2 p;
		p.x = cx;
		p.y = cy;

		// 距離を測る
		float len = GetLength(p);

		float cos = cosf(radian);
		float sin = sinf(radian);

		// 回転行列として定義されている
		// cosθ - sinθ x
		// sinθ - cosθ y

		// 回転公式(加法定理)
		x = (cos * cx) - (sin * cy);
		y = (sin * cx) + (cos * cy);
	}


	void Rotation2D2(
		float radian,
		float& x,
		float& y
	) {

		x = x * cosf(radian);
		y = y * sinf(radian);
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


	XMMATRIX Calc2DProj(
		const float window_width,
		const float window_height
	) {


		XMMATRIX proj =
			XMMatrixOrthographicOffCenterLH(0.0f,
				window_width, window_height, 0.0f, 0.0f, 1.0f);

		// スクリーン(-1.f,1.f,)(1.f,-1.f)
		XMFLOAT4X4 proj2;

		Math::TSXMfloat4x4::IdentityMatrix(&proj2);

		// 縦の比率分横を割る
		// h / w

		// (ピクセル * 2) / 縦スクリーン
		proj2._11 = 2 / window_width;
		// y座標の反転(現在上方向y軸なので)
		proj2._22 = (-2 / window_height);

		// 原点に戻すオフセット行列作成
		XMFLOAT4X4 offset;

		Math::TSXMfloat4x4::IdentityMatrix(&offset);

		// スクリーン比率から原点は左上なので
		// x += -1.f y += 1.f;
		offset._41 = -1;
		offset._42 = 1;

		// XMMATRIXに変換
		XMMATRIX proj_xmat, xoffset;

		// 単位行列化
		proj_xmat =
			XMMatrixIdentity();

		xoffset =
			XMMatrixIdentity();

		Math::ConvertMat::XMFLOAT4X4ToXMMATRIX(&proj_xmat, proj2);
		Math::ConvertMat::XMFLOAT4X4ToXMMATRIX(&xoffset, offset);

		// オフセット射影行列の作成
		proj_xmat = proj_xmat * xoffset;

		return proj_xmat;
	}
}


namespace Math {


	namespace TSXMfloat4x4 {


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

		void ClearXMFLOAT4X4(
			XMFLOAT4X4* out
		) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					out->m[i][j] = 0.f;
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


		void InverseMatrixSweepingMethod(
			XMFLOAT4X4* inv_a,
			XMFLOAT4X4& a
		) {
			/*
			// 行列の基本変形
			// 一つの行列を何倍かする(0倍は含まない)
			// 二つの行列を入れ替える
			// 一つの行に他の行の何倍かを加える

			// 右に単位行列を設置し、
			// 左にある行列を単位行列にする
			// A I → I X
			// その結果 X行列が逆行列となる

			//double a[4][4] = { {1,2,0,-1},{-1,1,2,0},{2,0,1,1},{1,-2,-1,1} }; //入力用の配列
			//double inv_a[4][4]; //ここに逆行列が入る
			double buf; //一時的なデータを蓄える
			int i, j, k; //カウンタ
			int n = 4;  //配列の次数

			//単位行列を作る
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					inv_a->m[i][j] = (i == j) ? 1.0 : 0.0;
				}
			}
			//掃き出し法
			for (i = 0; i < n; i++) {
				buf = 1 / a.m[i][i];
				for (j = 0; j < n; j++) {
					a.m[i][j] *= buf;
					inv_a->m[i][j] *= buf;
				}
				for (j = 0; j < n; j++) {
					if (i != j) {
						buf = a.m[j][i];
						for (k = 0; k < n; k++) {
							a.m[j][k] -= a.m[i][k] * buf;
							inv_a->m[j][k] -= inv_a->m[i][k] * buf;
						}
					}
				}
			}*/
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

			out->_11 = 1.f; out->_12 = 0.f; out->_13 = 0.f; out->_14 = 0.f;
			out->_21 = 0.f; out->_22 = 1.f; out->_23 = 0.f; out->_24 = 0.f;
			out->_31 = 0.f; out->_32 = 0.f; out->_33 = 1.f; out->_34 = 0.f;
			out->_41 = 0.f; out->_42 = 0.f; out->_43 = 0.f; out->_44 = 1.f;

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

			// 全て0にする
			ClearXMFLOAT4X4(out);

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

		void TestMultipleXMFLOAT4X4(
			XMFLOAT4X4* out,
			XMFLOAT4X4& mat1,
			XMFLOAT4X4& mat2
		) {
			float m = 0.f;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {

						// 行
						m += mat1.m[i][k] * mat2.m[k][i];
					}

					out->m[i][j] = m;
					m = 0.f;
				}
			}

		}

		void TSMatrixTranslation(
			XMFLOAT4X4* out,
			const XMFLOAT3& trans
		) {

			// _41 _42 _43
			out->_11 = 1.f; out->_12 = 0.f; out->_13 = 0.f; out->_14 = 0.f;
			out->_21 = 0.f; out->_22 = 1.f; out->_23 = 0.f; out->_24 = 0.f;
			out->_31 = 0.f; out->_32 = 0.f; out->_33 = 1.f; out->_34 = 0.f;
			out->_41 = trans.x; out->_42 = trans.y; out->_43 = trans.z; out->_44 = 1.f;
		}


		void TSMatrixScale(
			XMFLOAT4X4* out,
			const XMFLOAT3& float3
		) {

			// _11 _22 _33
			out->_11 = float3.x; out->_12 = 0.f; out->_13 = 0.f; out->_14 = 0.f;
			out->_21 = 0.f; out->_22 = float3.y; out->_23 = 0.f; out->_24 = 0.f;
			out->_31 = 0.f; out->_32 = 0.f; out->_33 = float3.z; out->_34 = 0.f;
			out->_41 = 0.f; out->_42 = 0.f; out->_43 = 0.f; out->_44 = 1.f;

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
			const float& radian
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
			const float& radian
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
			const float& radian
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
			const float& degrees
		) {
			TSMatrixRotationX(
				out_mat,
				DegreesToRad(degrees)
			);
		}

		void TSMatrixRotationYDegrees(
			XMFLOAT4X4* out_mat,
			const float& degrees
		) {
			TSMatrixRotationY(
				out_mat,
				DegreesToRad(degrees)
			);
		}


		void TSMatrixRotationZDegrees(
			XMFLOAT4X4* out_mat,
			const float& degrees
		) {
			

			TSMatrixRotationZ(
				out_mat,
				DegreesToRad(degrees)
			);
		}


		void TsSRTRotationZYXMatrix(
			XMFLOAT4X4*out_mat,
			const XMFLOAT3& pos,
			const XMFLOAT3& rotation,
			const XMFLOAT3& get_scale
		) {

			XMFLOAT4X4 trans, scale;
			XMFLOAT4X4 rot_x, rot_y, rot_z,total_rot;

			// 単位化
			IdentityMatrix(&total_rot);
			IdentityMatrix(&trans);
			IdentityMatrix(&scale);
			IdentityMatrix(&rot_x);
			IdentityMatrix(&rot_y);
			IdentityMatrix(&rot_z);

			// 移動
			TSMatrixTranslation(&trans, pos);

			// 拡縮
			TSMatrixScale(&scale, get_scale);

			// 回転
			TSMatrixRotationXDegrees(&rot_x, rotation.x);
			TSMatrixRotationYDegrees(&rot_y, rotation.y);
			TSMatrixRotationZDegrees(&rot_z, rotation.z);
			
			// 回転行列作成
			MultipleXMFLOAT4X4(&total_rot, rot_z,rot_y);
			MultipleXMFLOAT4X4(&total_rot, total_rot, rot_x);

			// 拡縮 * 回転 * 移動
			MultipleXMFLOAT4X4(out_mat, scale, total_rot);
			MultipleXMFLOAT4X4(out_mat, *out_mat, trans);

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
			Math::Cross::CrossXMFLOAT3(
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

			Math::Cross::CrossXMFLOAT3(
				&y_axis,
				z_axis,
				x_axis
			);

			// 単位ベクトル化
			CalcNormalize(y_axis);

			out_mat->_11 = x_axis.x;
			out_mat->_12 = x_axis.y;
			out_mat->_13 = x_axis.z;
			out_mat->_14 = 0;

			out_mat->_21 = y_axis.x;
			out_mat->_22 = y_axis.y;
			out_mat->_23 = y_axis.z;
			out_mat->_24 = 0;

			out_mat->_31 = z_axis.x;
			out_mat->_32 = z_axis.y;
			out_mat->_33 = z_axis.z;
			out_mat->_34 = 0;

			// カメラの座標軸とカメラ座標の内積を行う
			//  = 移動値が出せる
			// cosからその方向の移動値が出せる
			//XMFLOAT3 vec;

			float p_x = 0.f,p_y = 0.f,p_z = 0.f;

			Dot::DotXMFLOAT3(&p_x, pos, x_axis);
			Dot::DotXMFLOAT3(&p_y, pos, x_axis);
			Dot::DotXMFLOAT3(&p_z, pos, x_axis);

			// 各行に代入する
			out_mat->_41 = p_x;
			out_mat->_42 = p_y;
			out_mat->_43 = p_z;
			out_mat->_44 = 1;

			// カメラを原点とするためには
			// 逆行列する必要がある
			// 逆行列とは単位行列に戻す行列
			// ワールド原点に戻す
			
			XMFLOAT4X4 inv;

			// 逆行列作成
			// 列行
			inv._11 = x_axis.x;
			inv._21 = x_axis.y;
			inv._31 = x_axis.z;
			inv._41 = 0.f;

			inv._12 = y_axis.x;
			inv._22 = y_axis.y;
			inv._32 = y_axis.z;
			inv._42 = 0.f;

			inv._13 = z_axis.x;
			inv._23 = z_axis.y;
			inv._33 = z_axis.z;
			inv._43 = 0.f;

			inv._14 = -p_x;
			inv._24 = -p_y;
			inv._34 = -p_z;
			inv._44 = 1.f;

			// 原点(オリジン)の位置に戻す
			MultipleXMFLOAT4X4(out_mat, *out_mat, inv);
		}

		//void TSInverseViewMatrix(
		//	XMFLOAT4X4* out,
		//	XMFLOAT4X4& in
		//) {
		//
		//
		//}


		void TSProjectionMatrix(
			XMFLOAT4X4* out,
			float angle, // 視野角
			float aspact,// アスペクト比
			float _far,  // クリップ値(far)
			float _near  // クリップ値(near)
		) {

			/*
			  プロジェクション行列作成情報
			  遠近感を作る行列
			  奥にあるほど縮める、近い物ほど大きくする
			  それが視推台という考え方

			  aspact = 投影する空間の縦横の比率

			  angle = 視野角

			  near = 前方クリップ面

			  far = 後方クリップ面

			*/

			// ScaleX
			out->_11 = (1 / tanf(angle / 2)) / aspact;
			out->_12 = 0.f;
			out->_13 = 0.f;
			out->_14 = 0.f;

			// ScaleY(画角による拡縮の値)
			out->_21 = 0.f;
			out->_22 = (1 / tanf(angle / 2));
			out->_23 = 0.f;
			out->_24 = 0.f;

			// ScaleZ
			out->_31 = 0.f;
			out->_32 = 0.f;
			out->_33 = (1 / (_far - _near) * _far);
			// 1(z値の拡縮に使うため)
			out->_34 = 1;

			out->_41 = 0.f;
			out->_42 = 0.f;
			// 移動z
			out->_43 = -_near / (_far - _near) * _far;
			out->_44 = 0.f;
		}


		void TSScreenMatrix(
			XMFLOAT4X4*out,
			float width,
			float height
		) {

			// クリップ空間からスクリーンに
			// 表示するためスクリーンに変換する

			// 拡大率、平行移動値のx,y成分にウィンドウサイズ / 2を設定する
			// これによって原点が左上に移動し、y軸も下が+に変換される

			out->_11 = width / 2;
			out->_12 = 0.f;
			out->_13 = 0.f;
			out->_14 = 0.f;

			out->_21 = 0.f;
			out->_22 = -(height / 2);
			out->_23 = 0.f;
			out->_24 = 0.f;

			out->_31 = 0.f;
			out->_32 = 0.f;
			out->_33 = 1.f;
			out->_34 = 0.f;

			out->_41 = width / 2;
			out->_42 = height / 2;
			out->_43 = 0.f;
			out->_44 = 1.f;
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
