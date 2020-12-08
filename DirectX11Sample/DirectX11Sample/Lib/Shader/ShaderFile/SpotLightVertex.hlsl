

struct VS_IN {
	float4 pos : POSITION0;
	float4 normal : NORMAL0;
	float4 color : COLOR0;
};


struct VS_OUT {

	float4 pos : SV_POSITION;
	float4 nor : NORMAL;
	float4 color : COLOR;
	float4 eye_dir : EYE_DIR;
};

cbuffer C_BUFFER {

	float4x4 WORLD;
	float4x4 PROJ;
	float4x4 VIEW;
	float4x4 SPOT_LIGHT_WORLD;  // スポットライトの回転、拡縮、移動
	float4 LIGHT_POS;           // ライト位置
	float LIGHT_ATTENUATION;    // ライト減衰数
	float4 SPOT_DIR;            // ライト方向
	float SPOT_THETA;           // スポットライトの扇の大きさ
	float SPOT_PHI;             // outer-cornの範囲
	float4 AMBIENT_COLOR;       // アンビエントカラー(環境光)
};


float4 main(VS_IN input) : SV_POSITION
{

	// ライトから頂点へのベクトルを出す
	float4 light_vec_dir =
		mul(input.pos,WORLD) - LIGHT_POS;

	// ライトから頂点の方向ベクトル(正規化済み)
	float4 light_vec_dir_n =
		normalize(light_vec_dir);

	// ライトから頂点への距離を出す
	float light_len =
		length(light_vec_dir);

	// 距離減衰
	float attenuation =
		1.f / (light_attenuation * light_len * light_len);

	// ライトベクトル正規化
	float4 light_vec_dir_n = normalize(light_vec_dir);

	// スポットライト方向正規化
	float4 spor_dir_n = normalize(SPOT_DIR);

	// 頂点からライトnとスポットライト方向nの内積cos
	float cos_alpha = dot(light_vec_dir_n, spor_dir_n);

	// cos値の半分(単位ベクトル)
	float cos_half_theta = cos(SPOT_THETA);

	// 単位ベクトルの範囲で光っているかどうかを比較する
	float cos_half_phi = cos(SPOT_PHI);

	// 単位ベクトルの範囲に入っているかどうか
	if (cos_alpha <= cos_half_theta) {

		// 入っていない
		color = AMBIENT_COLOR;
		return;
	}
	else {

		// 入っている
		attenuation *= pow();
	}

	return pos;
}