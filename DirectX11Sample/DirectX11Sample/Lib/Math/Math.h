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
	* @brief ���W�A��(1.f ~ 0.f)�ϊ�
	*/
	float DegreesToRad(
		float degrees
	);


	/**
	* @brief �f�B�O���[(�p)�ϊ�
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
		* @brief ���
		*/
		void SubXMFLOAT4X4(
			XMFLOAT4X4* out,
			const XMFLOAT4X4& mat
		);


		/**
		* @brief ���������ǂ���
		*/
		bool IsXMFLOAT4X4Match(
			const XMFLOAT4X4& m1,
			const XMFLOAT4X4& m2
		);

		/**
		* @brief �s���S��0�ɂ���
		*/
		void ClearXMFLOAT4X4(
			XMFLOAT4X4*out
		);


		/**
		* @brief �|�����킹�s��
		*/
		void MultipleXMFLOAT4X4(
		XMFLOAT4X4*out,
			XMFLOAT4X4&mat1,
			XMFLOAT4X4&mat2
		);

		/**
		* @brief �������̊|�����킹�s��
		*/
		void TestMultipleXMFLOAT4X4(
			XMFLOAT4X4* out,
			XMFLOAT4X4& mat1,
			XMFLOAT4X4& mat2
		);

		/**
		* @brief �|���o���@��p�����t�s��ϊ�
		*/
		void InverseMatrixSweepingMethod(
			XMFLOAT4X4* out,
			XMFLOAT4X4&in
		);


		/**
		* @brief �]�u�s��
		*/
		void TransposeXMFLOAT4X4(
			XMFLOAT4X4* out
		);


		/**
		* @brief �]�u�s��2
		*/
		XMFLOAT4X4 TransposeXMFLOAT4X4(
			XMFLOAT4X4& out
		);


		/**
		* @brief �P�ʍs��
		*/
		void IdentityMatrix(
			XMFLOAT4X4* out
		);


		// �A�t�B���ϊ�
		/*
		float        sx, _12, _13, _14;
		float        _21, sy, _23, _24;
		float        _31, _32, _sz, _34;
		float        tx, ty, tz, _44;
		*/

		/**
		* @brief ���[���h���W�ϊ��s��
		*/
		void TSMatrixTranslation(
			XMFLOAT4X4* out_mat,
			const XMFLOAT3& trans
		);


		/**
		* @brief �g�k�ϊ��s��
		*/
		void TSMatrixScale(
			XMFLOAT4X4* out_mat,
			const XMFLOAT3& mat
		);


		/**
		* @brief X����]�s��
		*/
		void TSMatrixRotationX(
			XMFLOAT4X4* out_mat,
			const float& radian
		);


		/**
		* @brief �f�B�O���[��
		*/
		void TSMatrixRotationXDegrees(
			XMFLOAT4X4* out_mat,
			const float& degrees
		);

		/**
		* @brief Y����]�s��
		*/
		void TSMatrixRotationY(
			XMFLOAT4X4* out_mat,
			const float& radian
		);


		/**
		* @brief Y����]�s��
		*/
		void TSMatrixRotationYDegrees(
			XMFLOAT4X4* out_mat,
			const float&degrees
		);

		/**
		* @brief Z����]�s��
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
		* @brief �X�P�[����]�ړ��s��v�Z
		*/
		void TsSRTRotationZYXMatrix(
			XMFLOAT4X4* out_mat,
			const XMFLOAT3& pos,
			const XMFLOAT3& rotation,
			const XMFLOAT3& scale
		);


		/**
		* @brief �J�������W�̋t�s��
		*/
		void TSInverseViewMatrix(
			XMFLOAT4X4* out,
			XMFLOAT4X4& in
		);


		/**
		* @brief �r���[�ϊ��s��
		*/
		void TSViewMatrix(
			XMFLOAT4X4* out_mat,
			XMFLOAT3& pos,
			XMFLOAT3& look,
			XMFLOAT3& up_dir_vec
		);


		/**
		* @brief �v���W�F�N�V�����ϊ��s��
		*/
		void TSProjectionMatrix(
			XMFLOAT4X4* out,
			float angle,
			float aspact,
			float _far,
			float _near
		);


		/**
		* @brief �X�N���[���ϊ��s��
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
		* @brief Mat * Vec = Vec2 �ϊ�
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
		* @brief ���όv�Z�@���ʂɍs���΃X�J���[�l���Ԃ��Ă���
		* @brief ���̑��ɂǂ��炩��P�ʂ������cos�l�����o����
		*/
		void DotXMFLOAT3(
			float* out_vec,
			XMFLOAT3& vec1,
			XMFLOAT3& vec2
		);


		/**
		* @brief �����`�F�b�N�Ɛ��ƕ��`�F�b�N
		* @return ���� = 0 �� = 1 �� = -1 �G���[ = -2
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
