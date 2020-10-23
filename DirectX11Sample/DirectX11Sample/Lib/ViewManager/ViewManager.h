#ifndef VIEW_H_
#define VIEW_H_


#include<wrl.h>
#include<d3d11.h>
#include<map>
#include<string>


//! DirectX版のスマートポインタ
using namespace Microsoft::WRL;


/**
* @class ViewManager
* @brief DirectX11のView系を管理するクラス
*/
class ViewManager {
public:

	/** @define 最初のDEVICE用 */
	const std::string DEVICE_RENDER_TARGET_VIEW = "DeviceView";

public:


	/**
	* @brief レンダーターゲット作成
	*/
	bool CreateRenderTargetView(
		const std::string& view_name
	);


	/**
	* @brief クライアントサイズの深度ステンシルビュー作成
	*/
	bool CreateClientSizeDepthStencilView(
		const std::string& window_class_name
	);


	/**
	* @brief 深度ステンシル作成
	*/
	bool CreateDepthStencilView(
		const std::string& view_name,
		const D3D11_TEXTURE2D_DESC& desc,
		const D3D11_DEPTH_STENCIL_VIEW_DESC& dsv_desc
	);

	void DestoryRenderTargetView(const std::string&view_name);
	void DestoryDepthStencilView(const std::string& view_name);
	void DestoryDepthStencilTexture(const std::string& view_name);


	/**
	* @brief 解放
	*/
	void Release();

	ComPtr<ID3D11RenderTargetView> GetPtrRenderTargetView(
		const std::string& view_name
	);
	ComPtr<ID3D11DepthStencilView> GetPtrDepthStencilView(
		const std::string& view_name
	);
	ComPtr<ID3D11Texture2D> GetPtrDepthStencilTexture(
		const std::string& view_name
	);


public:


	//! レンダーターゲットビューを管理
	std::map<std::string, ComPtr<ID3D11RenderTargetView>>
		mp_render_target_view_list;

	//! ステンシルビューのリストを管理
	std::map<std::string, ComPtr<ID3D11DepthStencilView>>
		mp_depth_stencil_view_list;

	//! ID3D11DepthStencilViewを生成するためのテクスチャ
	std::map<std::string, ComPtr<ID3D11Texture2D>>
		mp_depth_stencil_texture_list;
};

#endif
