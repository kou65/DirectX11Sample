

struct VS_IN {
	float4 pos : POSITION0;
	float4 color : COLOR0;
};


struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};


cbuffer Buf2D{
	float4x4 WORLD;
	float4x4 PROJ;
};


VS_OUT main(VS_IN input)
{

	VS_OUT output;

	// ˆÊ’u•ÏŠ·
	float4 out_pos = mul(input.pos,WORLD);

	// 2D•ÏŠ·
	out_pos = mul(out_pos,PROJ);

	output.pos = out_pos;
	output.color = input.color;

	return output;
}