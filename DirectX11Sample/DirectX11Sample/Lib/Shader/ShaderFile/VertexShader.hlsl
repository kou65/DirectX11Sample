

// VertexShader�ɑ����Ă���f�[�^�\��
struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};


// VertexShader����o�͂���f�[�^�\��
struct VS_OUT {
	float4 pos :SV_POSITION;
	float4 col : COLOR0;
};


cbuffer ConstantBuffer {

	// ���[���h�ϊ��s��
	float4x4 world;
	// �r���[�ϊ��s��
	float4x4 view;
	// �����ˉe�ϊ��s��
	float4x4 projection;
};


VS_OUT main(VS_IN input)
{
	VS_OUT output;

output.pos = input.pos;
output.col = input.col;

	return output;
}