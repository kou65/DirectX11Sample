

// VertexShaderに送られてくるデータ構造
struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR;
};


// VertexShaderから出力するデータ構造
struct VS_OUT {
	float4 pos :SV_POSITION;
	float4 col : COLOR;
};


VS_OUT main(VS_IN input)
{
	VS_OUT output;

output.pos = input.pos;
output.col = input.col;

	return output;
}