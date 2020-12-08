

struct VS_IN {
	float4 pos : POSITION0;
	float4 normal : NORMAL0;
	float4 color : COLOR0;
};


struct VS_OUT {

	float4 pos : SV_POSITION;
	float4 nor : NORMAL;
	float4 color : COLOR;
	float4 eye_dir : EYE_DIR;
};

cbuffer C_BUFFER {

	float4x4 WORLD;
	float4x4 PROJ;
	float4x4 VIEW;
	float4x4 SPOT_LIGHT_WORLD;  // �X�|�b�g���C�g�̉�]�A�g�k�A�ړ�
	float4 LIGHT_POS;           // ���C�g�ʒu
	float LIGHT_ATTENUATION;    // ���C�g������
	float4 SPOT_DIR;            // ���C�g����
	float SPOT_THETA;           // �X�|�b�g���C�g�̐�̑傫��
	float SPOT_PHI;             // outer-corn�͈̔�
	float4 AMBIENT_COLOR;       // �A���r�G���g�J���[(����)
};


float4 main(VS_IN input) : SV_POSITION
{

	// ���C�g���璸�_�ւ̃x�N�g�����o��
	float4 light_vec_dir =
		mul(input.pos,WORLD) - LIGHT_POS;

	// ���C�g���璸�_�̕����x�N�g��(���K���ς�)
	float4 light_vec_dir_n =
		normalize(light_vec_dir);

	// ���C�g���璸�_�ւ̋������o��
	float light_len =
		length(light_vec_dir);

	// ��������
	float attenuation =
		1.f / (light_attenuation * light_len * light_len);

	// ���C�g�x�N�g�����K��
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
		color = AMBIENT_COLOR;
		return;
	}
	else {

		// �����Ă���
		attenuation *= pow();
	}

	return pos;
}