

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
    float4x4 world;         //���[���h�ϊ��s��
    float4x4 view;          //�r���[�ϊ��s��
    float4x4 projection;    //�����ˉe�ϊ��s��
}


VS_OUT main(VS_IN input)
{
    VS_OUT output;

    // 3D���W�ϊ�
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);

    // �F�͂��̂܂ܓn��
    output.col = input.col;

    return output;
}