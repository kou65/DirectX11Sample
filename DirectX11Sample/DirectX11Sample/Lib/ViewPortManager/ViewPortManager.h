#ifndef VIEWPORT_MANAGER_H_
#define VIEWPORT_MANAGER_H_

#include<d3d11.h>
#include<string>
#include<map>

/**
* @brief ビューポート管理者
*/
class ViewPortManager {


	/**
	* @brief ビューポート作成
	*/
	bool Set(
		const std::string& view_name,
		const D3D11_VIEWPORT&view_port
	);


	/**
	* @brief 削除
	*/
	void DestoryViewPort(const std::string& view_name);



private:

	/**
	* @brief ビューポートの設定
	*/
	bool SetUpViewPort(
		const std::string& window_class_name
	);


private:

	//! ビューポート
	std::map<std::string, D3D11_VIEWPORT>
		mp_view_port_list;
};

#endif
