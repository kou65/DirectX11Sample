

struct VS_IN
{
    float4 pos : POSITION0;
    float4 nor : NORMAL0;
    float4 col : COLOR0;
};


struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};


cbuffer ConstantBuffer
{
    float4x4 world;         //ワールド変換行列
    float4x4 view;          //ビュー変換行列
    float4x4 projection;    //透視射影変換行列
}


VS_OUT main(VS_IN input)
{
    VS_OUT output;

    // 3D座標変換
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    // 色はそのまま渡す
    output.col = input.col;

    return output;
}