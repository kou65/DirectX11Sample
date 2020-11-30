#ifndef MATERIAL_DATA_H_
#define MATERIAL_DATA_H_



#include<DirectXMath.h>


using namespace DirectX;


/**
* @brief マテリアル情報を含んだデータ構造体
*/
struct MaterialData {

	XMFLOAT4 ambient;   // アンビエント(環境光)
	XMFLOAT4 diffuse;   // ディフューズ(拡散光)
	XMFLOAT4 specular;  // スペキュラー(反射光)
};

#endif
