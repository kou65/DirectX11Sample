

struct VS_OUT {

	float4 pos : SV_POSITION;
	float4 normal : NORMAL;
	float4 color : COLOR;
	float4 eye_dir : EYE_DIR;
};


float4 main(VS_OUT vs_out) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}