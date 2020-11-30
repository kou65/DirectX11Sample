

struct PS_IN {
	float4 pos : SV_POSITION;
	float4 nor : NORMAL;
	float nl :   NL;
	float4 col : COLOR;
	float4 eye_dir : EYE_DIR;
	float4 light_vector : LIGHT_VECTOR;
	float4 world_pos : WORLD_POS;
	float ll : LL; // ポリゴン座標とライトのベクトルとライトのベクトルの内積
};


cbuffer ConstantBuffer
{
	float4x4	World;				// ワールド変換行列
	float4x4	View;				// ビュー変換行列
	float4x4	Projection;			// 透視射影変換行列
	float4		CameraPos;			// カメラ座標
	float4		LightPos;			// ライト座標
	float4		LightVector;		// ライト方向
	float4		LightColor;			// ライトカラー
	float4		MaterialAmbient;	// アンビエント
	float4		MaterialDiffuse;	// ディフューズ
	float4		MaterialSpecular;	// スペキュラー
}

// Textureをスロット0の0番目のテクスチャレジスタに設定
Texture2D tex : register(t0[0]);

// Samplerをスロット0の0番目のサンプラレジスタに設定
SamplerState samp : register(s0[0]);


float4 main(PS_IN input) : SV_TARGET
{

	float ambient_factor = MaterialAmbient[3];
float diffuse_factor = MaterialDiffuse[3];

float4 ambient_color = MaterialAmbient * ambient_factor;

/*
		input.color => 頂点カラー
		LightColor => ライトカラー
		MaterialDiffuse => マテリアルの拡散光
		input.nl => 法線とライトの内積結果
	*/
float4 diffuse_color =
input.nl * (input.col * LightColor * MaterialDiffuse * diffuse_factor);

float4 out_color;

// アンビエントカラー + ディフューズカラー
// ランバート
out_color = diffuse_color + ambient_color;

float4 light_vector = LightVector;

// ポイントライト、スポットライト用
light_vector = input.light_vector;

// フォン
// 反射ベクトルの算出
float4 reflect = 
normalize(2 * input.nl * input.nor - light_vector);

// スペキュラー反射
float4 specular = 
pow(saturate(dot(reflect, input.eye_dir)), 16);

// 反射
out_color += (specular * float4(1.f, 1.f, 1.f, 1.f));

// スポットライト
if (input.ll < 0.8) {

	out_color *= 0.1f;
}

float distance =
length(input.world_pos - LightPos);

float attenuate = 1.f / (0.2f + 0.1f * distance + 0.1f *
	distance * distance);

out_color *= attenuate;

	return out_color;
}


// 光の減衰
	/*
		減衰の計算式
			1.0 / (a + b * distance + c * distance * distance)

			distance：ライトとの距離
			a：ライト全体の明るさ
			b：近距離の減衰率に関係する
			c：遠距離の減衰率に関係する
			a、b、c共通：0に小さい値の方がライトの影響が強くなる
	*/


	/*
		例①：
			distance => 5.0
			a => 0.1
			b => 0.1
			c => 0.1

			1.0 / (0.1 + 0.1 * 5.0 + 0.1 * 5.0 * 5.0)
			1.0 / (0.1 + 0.5 + 2.5)
			1.0 / (3.1)
			0.3

		例②：
			distance => 5.0
			a => 0.4
			b => 0.4
			c => 0.4

			1.0 / (0.4 + 0.4 * 5.0 + 0.4 * 5.0 * 5.0)
			1.0 / (0.4 + 2.0 + 10.0)
			1.0 / (12.4)
			0.08

		例③：
			distance => 5.0
			a => 1
			b => 1
			c => 1

			1.0 / (1 + 1 * 5.0 + 1 * 5.0 * 5.0)
			1.0 / (1 + 5.0 + 25.0)
			1.0 / (31.0)
			0.03
	*/