
#ifndef COLLISION_H
#define COLLISION_H

#include"../../../Vec3/Vec3.h"
#include"../../../Vec2/Vec2.h"
#include"../CollisionData/Rect3D/Rect3D.h"
#include"../CollisionData/Point/Point.h"
#include"../CollisionData/Fan/Fan.h"
#include"../CollisionData/AABB/AABB.h"



/**
* @namespace Collision 衝突系関数ネームスペース
*/
namespace Collision {

	/* 引数の説明 */

	/**
	* @brief 球と球
	* @param[in] 1,オブジェクト1の座標
    * @param[in] 2,オブジェクト2の座標
    * @param[in] 3,オブジェクト1の半径
    * @param[in] 4,オブジェクト2の半径
    * rad_1,rad2は半径の大きさ
    * (中心から〇を出したい場合は中心の座標から当たり判定に入れこむこと)
	*/
	bool IsHitSphereAndSphere(
		Vec3 v1,
		Vec3 v2,
		float rad_1,
		float rad_2
	);


	/**
	* @brief 円と円
	* @param[in] オブジェクト1の座標
	* @param[in] オブジェクト2の座標
	* @param[in] オブジェクト1の半径
	* @param[in] オブジェクト2の半径
	*/
	bool IsHitCircleAndCircle(
		Vec2 v1,
		Vec2 v2,
		float rad_1,
		float rad_2
	);


	/**
	* @brief AABBとの当たり判定
	* @param[in] box1 AABB
	* @param[in] box2 AABB
	*/
	bool IsHitAABBAndAABB(
		const AABB&box1,
		const AABB&box2
	);


	/**
	* @brief aabbと球の当たり判定
	* @param[in] box1 AABB
	* @param[in] sphere 球
	*/
	bool IsHitAABBAndSphere(
		const AABB&box1,
		const Vec3 sph_pos,
		const float rad
	);


	// レイと球の衝突判定

	// lx, ly, lz : レイの始点
	// vx, vy, vz : レイの方向ベクトル
	// px, py, pz : 球の中心点の座標
	// r : 球の半径
	// q1x, q1y, q1z: 衝突開始点（戻り値）
	// q2x, q2y, q2z: 衝突終了点（戻り値）

	bool IsHitRayAndSphere(
		float lx, float ly, float lz,
		float vx, float vy, float vz,
		float px, float py, float pz,
		float r,
		float &q1x, float &q1y, float &q1z,
		float &q2x, float &q2y, float &q2z
	);


	/**
	* 正方形と正方形の当たり判定 
	*/
	bool IsHitCubeAndCube(
		const Rect3D&rect1,
		const Rect3D&rect2
	);

	/**
	* @brief 扇とポイントの当たり判定
	*/
	bool IsHitFanAndPoint(const Fan&fan,const Point&point);

	/*
	bool IsHitRayAndPoint(
		Vec3&v1,
		Vec3&v2
	);

	bool IsHitCapsuleAndCapsule(

	);
	*/
}

#endif