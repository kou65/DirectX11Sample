#ifndef VIEWPORT_MANAGER_H_
#define VIEWPORT_MANAGER_H_

#include<d3d11.h>
#include<string>
#include<map>

/**
* @brief �r���[�|�[�g�Ǘ���
*/
class ViewPortManager {


	/**
	* @brief �r���[�|�[�g�쐬
	*/
	bool Set(
		const std::string& view_name,
		const D3D11_VIEWPORT&view_port
	);


	/**
	* @brief �폜
	*/
	void DestoryViewPort(const std::string& view_name);



private:

	/**
	* @brief �r���[�|�[�g�̐ݒ�
	*/
	bool SetUpViewPort(
		const std::string& window_class_name
	);


private:

	//! �r���[�|�[�g
	std::map<std::string, D3D11_VIEWPORT>
		mp_view_port_list;
};

#endif
