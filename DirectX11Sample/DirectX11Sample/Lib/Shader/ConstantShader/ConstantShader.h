#ifndef CONSTANT_SHADER_H_
#define CONSTANT_SHADER_H_



namespace ConstantShader {


	/**
	* @enum Type
	* @brief ���_�V�F�[�_�[�̎��
	*/
	enum class VSType {
		NORMAL,
		VS3D,
		VARIOUS_LIGHT,
		TOTAL,
	};


	/**
	* @enum Type
	* @brief ���_�V�F�[�_�[�̎��
	*/
	enum class PSType {
		NORMAL,
		VARIOUS_LIGHT,
		TOTAL,
	};
}

#endif
