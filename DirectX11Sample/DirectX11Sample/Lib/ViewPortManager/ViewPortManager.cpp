#include"ViewPortManager.h"
#include"../Device/Device.h"
#include"../SingletonTemplate/SingletonTemplate.h"



bool ViewPortManager::Set(
	const std::string& view_name,
	const D3D11_VIEWPORT& view_port
) {
	mp_view_port_list[view_name] = view_port;

	return true;
}


void ViewPortManager::DestoryViewPort(const std::string& view_name) {

	// 探す
	decltype(mp_view_port_list)::iterator it =
		mp_view_port_list.find(view_name);

	// endが帰ってきていないなら見つかった
	if (it != mp_view_port_list.end()) {

		mp_view_port_list[view_name];
		mp_view_port_list.erase(it);
	}
}


bool ViewPortManager::SetUpViewPort(
	const std::string& window_class_name
) {

	HWND w_handle =
		FindWindowA(window_class_name.c_str(), nullptr);

	if (w_handle == nullptr) {
		return false;
	}

	RECT rect;

	GetClientRect(w_handle, &rect);

	//ビューポートの設定
	D3D11_VIEWPORT view_port;
	view_port.TopLeftX = 0;							   // 左上X座標
	view_port.TopLeftY = 0;							   // 左上Y座標
	view_port.Width =
		static_cast<float>(
		(rect.right - rect.left));                     // 横幅
	view_port.Height =
		static_cast<float>(
		(rect.bottom - rect.top));                     // 縦幅
	view_port.MinDepth = 0.0f;						   // 最小深度
	view_port.MaxDepth = 1.0f;						   // 最大深度

	Singleton<Device>::GetInstance()->GetPtrImmContext()
	->RSSetViewports(
		1,					// 設定するビューポートの数
		&view_port);		// 設定するビューポート情報のポインタ

	return true;
}
