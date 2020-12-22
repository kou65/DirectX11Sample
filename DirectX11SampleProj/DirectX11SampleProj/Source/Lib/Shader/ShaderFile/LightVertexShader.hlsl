

struct VS_IN {
	float4 pos : POSITION0;
	float4 nor : NORMAL0;
	float4 color : COLOR0;
};



struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 nor : NORMAL;
	float nl : NL;
	float4 color : COLOR;

	float4 eye_dir : EYE_DIR;
	float4 light_vector : LIGHT_VECTOR;
	float4 world_pos : WORLD_POS;
	// �|���S�����W�ƃ��C�g�̃x�N�g���ƃ��C�g�̃x�N�g���̓���
	float ll : LL;
};


cbuffer ConstantBuffer {

	float4x4 world;             // ���[���h�ϊ��s��
	float4x4 view;              // �r���[�ϊ��s��
	float4x4 proj;              // �����ˉe�ϊ��s��
	float4   camera_pos;        // �J�������W
	float4   light_pos;         // ���C�g���W
	float4   light_vector;      // ���C�g����
	float4   light_color;       // ���C�g�J���[
	float4   material_ambient;  // �A���r�G���g
	float4   material_diffuse;  // �f�B�t���[�Y
	float4   material_specular; // �X�y�L�����[
};


VS_OUT main(VS_IN input)
{

	VS_OUT out_put;

// ���[�J�� * ���[���h
out_put.world_pos = mul(input.pos, world);
// ���[���h * �r���[
out_put.pos = mul(out_put.world_pos, view);
// �r���[ * �v���W�F�N�V����
out_put.pos = mul(out_put.pos, proj);


// ���_�J���[
out_put.color = input.color;

// �ړ����v�Z�ɔ��f�����Ȃ�
input.nor.w = 0.f;

// ���_�̖@���Ƀ��[���h�s��(���݈ʒu���])���|�����킹��
// ���[���h���W��ł̖@���̌����ɕϊ�����
out_put.nor = mul(input.nor, world).xyzw;

// �P�ʃx�N�g����
out_put.nor = normalize(out_put.nor);


// �f�B���N�V���i�����C�g(���̕����Ɍ��𓖂Ă�)
// saturate => �����Ŏw�肵���l��0�`1�ł͈̔͂Ɏ��߂�
// dot => ���όv�Z
out_put.nl = saturate(dot(out_put.nor, -light_vector));


// �|�C���g���C�g(�_����)
// ���C�g�̈ʒu�ƃ|���S���̍��W�Ńx�N�g�����Z�o����
// ���C�g�ƃ|���S�����W�̃x�N�g���̓|���S������̃x�N�g���Ƃ��ĎZ�o
out_put.light_vector = normalize(light_pos - out_put.world_pos);
out_put.nl = saturate(dot(out_put.nor, out_put.light_vector));

// �X�|�b�g���C�g
out_put.light_vector = normalize(light_pos - out_put.world_pos);
out_put.nl = saturate(dot(out_put.nor, out_put.light_vector));

// ���C�g�̕����ƃ|���S���ƃ��C�g�̃x�N�g��
out_put.ll = saturate(dot(light_vector, -out_put.light_vector));

// �t�H������(�J�������W���烏�[���h���W�܂ł̕����𐳋K��)
out_put.eye_dir = normalize(camera_pos - out_put.world_pos);

	return out_put;
}