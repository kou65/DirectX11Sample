

struct PS_IN {
	float4 pos : SV_POSITION;
	float4 nor : NORMAL;
	float nl :   NL;
	float4 col : COLOR;
	float4 eye_dir : EYE_DIR;
	float4 light_vector : LIGHT_VECTOR;
	float4 world_pos : WORLD_POS;
	float ll : LL; // �|���S�����W�ƃ��C�g�̃x�N�g���ƃ��C�g�̃x�N�g���̓���
};


cbuffer ConstantBuffer
{
	float4x4	World;				// ���[���h�ϊ��s��
	float4x4	View;				// �r���[�ϊ��s��
	float4x4	Projection;			// �����ˉe�ϊ��s��
	float4		CameraPos;			// �J�������W
	float4		LightPos;			// ���C�g���W
	float4		LightVector;		// ���C�g����
	float4		LightColor;			// ���C�g�J���[
	float4		MaterialAmbient;	// �A���r�G���g
	float4		MaterialDiffuse;	// �f�B�t���[�Y
	float4		MaterialSpecular;	// �X�y�L�����[
}

// Texture���X���b�g0��0�Ԗڂ̃e�N�X�`�����W�X�^�ɐݒ�
Texture2D tex : register(t0[0]);

// Sampler���X���b�g0��0�Ԗڂ̃T���v�����W�X�^�ɐݒ�
SamplerState samp : register(s0[0]);


float4 main(PS_IN input) : SV_TARGET
{

	float ambient_factor = MaterialAmbient[3];
float diffuse_factor = MaterialDiffuse[3];

float4 ambient_color = MaterialAmbient * ambient_factor;

/*
		input.color => ���_�J���[
		LightColor => ���C�g�J���[
		MaterialDiffuse => �}�e���A���̊g�U��
		input.nl => �@���ƃ��C�g�̓��ό���
	*/
float4 diffuse_color =
input.nl * (input.col * LightColor * MaterialDiffuse * diffuse_factor);

float4 out_color;

// �A���r�G���g�J���[ + �f�B�t���[�Y�J���[
// �����o�[�g
out_color = diffuse_color + ambient_color;

float4 light_vector = LightVector;

// �|�C���g���C�g�A�X�|�b�g���C�g�p
light_vector = input.light_vector;

// �t�H��
// ���˃x�N�g���̎Z�o
float4 reflect = 
normalize(2 * input.nl * input.nor - light_vector);

// �X�y�L�����[����
float4 specular = 
pow(saturate(dot(reflect, input.eye_dir)), 16);

// ����
out_color += (specular * float4(1.f, 1.f, 1.f, 1.f));

// �X�|�b�g���C�g
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


// ���̌���
	/*
		�����̌v�Z��
			1.0 / (a + b * distance + c * distance * distance)

			distance�F���C�g�Ƃ̋���
			a�F���C�g�S�̖̂��邳
			b�F�ߋ����̌������Ɋ֌W����
			c�F�������̌������Ɋ֌W����
			a�Ab�Ac���ʁF0�ɏ������l�̕������C�g�̉e���������Ȃ�
	*/


	/*
		��@�F
			distance => 5.0
			a => 0.1
			b => 0.1
			c => 0.1

			1.0 / (0.1 + 0.1 * 5.0 + 0.1 * 5.0 * 5.0)
			1.0 / (0.1 + 0.5 + 2.5)
			1.0 / (3.1)
			0.3

		��A�F
			distance => 5.0
			a => 0.4
			b => 0.4
			c => 0.4

			1.0 / (0.4 + 0.4 * 5.0 + 0.4 * 5.0 * 5.0)
			1.0 / (0.4 + 2.0 + 10.0)
			1.0 / (12.4)
			0.08

		��B�F
			distance => 5.0
			a => 1
			b => 1
			c => 1

			1.0 / (1 + 1 * 5.0 + 1 * 5.0 * 5.0)
			1.0 / (1 + 5.0 + 25.0)
			1.0 / (31.0)
			0.03
	*/