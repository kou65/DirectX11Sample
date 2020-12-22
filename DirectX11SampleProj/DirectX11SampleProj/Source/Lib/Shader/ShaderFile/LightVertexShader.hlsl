

struct VS_IN {
	float4 pos : POSITION0;
	float4 nor : NORMAL0;
	float4 color : COLOR0;
};



struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 nor : NORMAL;
	float nl : NL;
	float4 color : COLOR;

	float4 eye_dir : EYE_DIR;
	float4 light_vector : LIGHT_VECTOR;
	float4 world_pos : WORLD_POS;
	// ポリゴン座標とライトのベクトルとライトのベクトルの内積
	float ll : LL;
};


cbuffer ConstantBuffer {

	float4x4 world;             // ワールド変換行列
	float4x4 view;              // ビュー変換行列
	float4x4 proj;              // 透視射影変換行列
	float4   camera_pos;        // カメラ座標
	float4   light_pos;         // ライト座標
	float4   light_vector;      // ライト方向
	float4   light_color;       // ライトカラー
	float4   material_ambient;  // アンビエント
	float4   material_diffuse;  // ディフューズ
	float4   material_specular; // スペキュラー
};


VS_OUT main(VS_IN input)
{

	VS_OUT out_put;

// ローカル * ワールド
out_put.world_pos = mul(input.pos, world);
// ワールド * ビュー
out_put.pos = mul(out_put.world_pos, view);
// ビュー * プロジェクション
out_put.pos = mul(out_put.pos, proj);


// 頂点カラー
out_put.color = input.color;

// 移動が計算に反映させない
input.nor.w = 0.f;

// 頂点の法線にワールド行列(現在位置や回転)を掛け合わせて
// ワールド座標上での法線の向きに変換する
out_put.nor = mul(input.nor, world).xyzw;

// 単位ベクトル化
out_put.nor = normalize(out_put.nor);


// ディレクショナルライト(一定の方向に光を当てる)
// saturate => 引数で指定した値を0～1での範囲に収める
// dot => 内積計算
out_put.nl = saturate(dot(out_put.nor, -light_vector));


// ポイントライト(点光源)
// ライトの位置とポリゴンの座標でベクトルを算出する
// ライトとポリゴン座標のベクトルはポリゴンからのベクトルとして算出
out_put.light_vector = normalize(light_pos - out_put.world_pos);
out_put.nl = saturate(dot(out_put.nor, out_put.light_vector));

// スポットライト
out_put.light_vector = normalize(light_pos - out_put.world_pos);
out_put.nl = saturate(dot(out_put.nor, out_put.light_vector));

// ライトの方向とポリゴンとライトのベクトル
out_put.ll = saturate(dot(light_vector, -out_put.light_vector));

// フォン鏡面(カメラ座標からワールド座標までの方向を正規化)
out_put.eye_dir = normalize(camera_pos - out_put.world_pos);

	return out_put;
}