

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

	float4x4 WORLD;             // ���[���h
	float4x4 PROJ;              // �ˉe�ϊ�
	float4x4 VIEW;              // �r���[�ϊ�
	float4x4 SPOT_LIGHT_WORLD;  // �X�|�b�g���C�g�̉�]�A�g�k�A�ړ�
	float4 LIGHT_POS;           // ���C�g�ʒu
	float LIGHT_ATTENUATION;    // ���C�g������
	float4 SPOT_DIR;            // ���C�g����
	float SPOT_THETA;           // �X�|�b�g���C�g�̐�̑傫��
	float SPOT_PHI;             // outer-corn�͈̔�
	float SPOT_FALL_OFF;        // �X�|�b�g�t�H�[���I�t
	float4 AMBIENT_COLOR;       // �A���r�G���g�J���[(����)
	float4 DIFFUSE_COLOR;       // �g�U��
	float4 SPECULAR_COLOR;      // ���ʔ��ˌ�
	float3 EYE_DIR;             // ���_�������K���x�N�g��
	float SPECULAR_SHININESS;   // �X�y�L�����[�P�x
};

cbuffer T {
	float4 i;
};

VS_OUT main(VS_IN input)
{

	// �O���Z�o
	VS_OUT output;

	// ���W�ϊ�
	output.pos = mul(input.pos, WORLD);
	output.pos = mul(output.pos, VIEW);
	output.pos = mul(output.pos, PROJ);
	
	// �@��
	output.normal = input.normal;

	// ���C�g���璸�_�ւ̃x�N�g�����o��
	float4 light_vec_dir =
		mul(input.pos,WORLD) - LIGHT_POS;

	// ���C�g���璸�_�ւ̋������o��
	float light_len =
		length(light_vec_dir);

	// ��������
	float attenuation =
		1.f / (LIGHT_ATTENUATION * light_len * light_len);

	// ���C�g���璸�_�̕����x�N�g��(���K���ς�)
	float4 light_vec_dir_n = normalize(light_vec_dir);

	// �X�|�b�g���C�g�������K��
	float4 spor_dir_n = normalize(SPOT_DIR);

	// ���_���烉�C�gn�ƃX�|�b�g���C�g����n�̓���cos
	float cos_alpha = dot(light_vec_dir_n, spor_dir_n);

	// cos�l�̔���(�P�ʃx�N�g��)
	float cos_half_theta = cos(SPOT_THETA);

	// �P�ʃx�N�g���͈̔͂Ō����Ă��邩�ǂ������r����
	float cos_half_phi = cos(SPOT_PHI);

	// �P�ʃx�N�g���͈̔͂ɓ����Ă��邩�ǂ���
	if (cos_alpha <= cos_half_theta) {

		// �����Ă��Ȃ�
		output.color = AMBIENT_COLOR;
		return output;
	}
	else {

		if (cos_alpha > cos_half_theta) {

		}
		else {

			// �����Ă���
			attenuation *= pow((cos_alpha - cos_half_phi) /
				(cos_half_theta - cos_half_phi), SPOT_FALL_OFF);
		}

	}

	// �@���̐��K��
	float3 normal_n = normalize(mul(input.normal, WORLD).xyz);

	// ���C�g
	float3 light = -light_vec_dir_n;

	// �g�U��
	float diffuse_power =
		clamp(dot(normal_n, light), 0.f, 1.f);

	// ���_����t�̕����Z�o
	float3 eye = -normalize(EYE_DIR);

	// �n�[�t�x�N�g��
	float3 half_vec = normalize(light + eye);

	// �X�y�L�����[
	float specular = pow(
		clamp(dot(normal_n, half_vec), 0.f, 1.f),
		SPECULAR_SHININESS
	);

	// �J���[�l
	output.color = input.color * DIFFUSE_COLOR * diffuse_power * 
		attenuation + AMBIENT_COLOR + SPECULAR_COLOR * specular;

	return output;
}