#ifndef MODEL_PRIMITIVE_H_
#define MODEL_PRIMITIVE_H_



#include<vector>
#include<map>
#include<string>
#include"../MeshPrimitive/MeshPrimitive.h"
#include"../../MaterialData/MaterialData.h"
#include"../../Shader/ConstShader/ConstShader.h"



/**
* @brief モデル原子クラス
*/
struct Model {
public:


	/**
	* @brief コンストラクタ
	*/
	Model() {};


	/**
	* @brief メッシュを返す
	*/
	MeshPrimitive GetMesh(const int&mesh_count) {
		return m_mesh_list[mesh_count];
	}


	/**
	* @brief 最大メッシュリストサイズを返す
	*/
	size_t GetMeshCount() {
		return m_mesh_list.size();
	}


	/**
	* @brief メッシュ追加
	*/
	void AddMesh(MeshPrimitive p_input_mesh) {

		m_mesh_list.emplace_back(p_input_mesh);
	}


	/**
	* @brief シェーダーvs識別番号セット
	*/
	void SetVSType(const ConstShader::VSType&vs_type) {
		m_vs_type = vs_type;
	}


	/**
	* @brief シェーダーps識別番号セット
	*/
	void SetPSType(const ConstShader::PSType& ps_type) {
		m_ps_type = ps_type;
	}


	/**
	* @brief シェーダーvs識別番号を返す
	*/
	ConstShader::VSType GetVSType() {
		return m_vs_type;
	}


	/**
	* @brief シェーダーps識別番号を返す
	*/
	ConstShader::PSType GetPSType() {
		return m_ps_type;
	}


private:


	//! メッシュ配列
	std::vector<MeshPrimitive>m_mesh_list;

	//! シェーダーvs識別番号をメッシュに埋め込む
	ConstShader::VSType m_vs_type;

	//! シェーダーps識別番号をメッシュに埋め込む
	ConstShader::PSType m_ps_type;


};
#endif
