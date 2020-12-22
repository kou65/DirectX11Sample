

struct VS_IN {

	float4 pos : POSITION0;
	float4 normal : NORMAL0;
	float4 color : COLOR0;
};


struct VS_OUT {

	float4 pos : SV_POSITION;
	float4 normal : NORMAL;
	float4 color : COLOR;
	float4 eye_dir : EYE_DIR;
};


cbuffer C_BUFFER {

	float4x4 WORLD;             // ワールド
	float4x4 PROJ;              // 射影変換
	float4x4 VIEW;              // ビュー変換
	float4x4 SPOT_LIGHT_WORLD;  // スポットライトの回転、拡縮、移動
	float4 LIGHT_POS;           // ライト位置
	float LIGHT_ATTENUATION;    // ライト減衰数
	float4 SPOT_DIR;            // ライト方向
	float SPOT_THETA;           // スポットライトの扇の大きさ
	float SPOT_PHI;             // outer-cornの範囲
	float SPOT_FALL_OFF;        // スポットフォールオフ
	float4 AMBIENT_COLOR;       // アンビエントカラー(環境光)
	float4 DIFFUSE_COLOR;       // 拡散光
	float4 SPECULAR_COLOR;      // 鏡面反射光
	float3 EYE_DIR;             // 視点方向正規化ベクトル
	float SPECULAR_SHININESS;   // スペキュラー輝度
};

cbuffer T {
	float4 i;
};

VS_OUT main(VS_IN input)
{

	// 外部算出
	VS_OUT output;

	// 座標変換
	output.pos = mul(input.pos, WORLD);
	output.pos = mul(output.pos, VIEW);
	output.pos = mul(output.pos, PROJ);
	
	// 法線
	output.normal = input.normal;

	// ライトから頂点へのベクトルを出す
	float4 light_vec_dir =
		mul(input.pos,WORLD) - LIGHT_POS;

	// ライトから頂点への距離を出す
	float light_len =
		length(light_vec_dir);

	// 距離減衰
	float attenuation =
		1.f / (LIGHT_ATTENUATION * light_len * light_len);

	// ライトから頂点の方向ベクトル(正規化済み)
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
		output.color = AMBIENT_COLOR;
		return output;
	}
	else {

		if (cos_alpha > cos_half_theta) {

		}
		else {

			// 入っている
			attenuation *= pow((cos_alpha - cos_half_phi) /
				(cos_half_theta - cos_half_phi), SPOT_FALL_OFF);
		}

	}

	// 法線の正規化
	float3 normal_n = normalize(mul(input.normal, WORLD).xyz);

	// ライト
	float3 light = -light_vec_dir_n;

	// 拡散光
	float diffuse_power =
		clamp(dot(normal_n, light), 0.f, 1.f);

	// 視点から逆の方向算出
	float3 eye = -normalize(EYE_DIR);

	// ハーフベクトル
	float3 half_vec = normalize(light + eye);

	// スペキュラー
	float specular = pow(
		clamp(dot(normal_n, half_vec), 0.f, 1.f),
		SPECULAR_SHININESS
	);

	// カラー値
	output.color = input.color * DIFFUSE_COLOR * diffuse_power * 
		attenuation + AMBIENT_COLOR + SPECULAR_COLOR * specular;

	return output;
}