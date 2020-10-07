#ifndef DEVICE_H_
#define DEVICE_H_

#include<d3d11.h>
#include<string>

#pragma comment(lib,"d3d11.lib")

#include<wrl.h>
#include"../SingletonTemplate/SingletonTemplate.h"


//! DirectX版のスマートポインタ
using namespace Microsoft::WRL;


/**
* @class Device
* @brief デバイス関係のクラス
*/
class Device {
public:


	/**
	* @brief 各デバイスの初期化
	* @return bool 初期化成功=true 失敗=false
	*/
	bool Init(
		const std::string&window_class_name,
		bool is_window_mode = true
	);


	/**
	* @brief 各デバイスの解放
	*/
	void Release();


	/**
	* @brief 描画開始
	*/
	void StartRendering();


	/**
	* @brief 描画終了
	*/
	void EndRendering();

private:


	/**
	* @brief デバイスとスワップチェーン(GPUへ送る機能)の作成
	*/
	bool CreateDeviceAndSwapChain(
		const std::string& window_class_name
	);


	/**
	* @brief セットパラメータDXGI
	* @param[in] class_name ウィンドウのクラス名を入れる
	* @param[out] out_desc DXGIのデスク情報
	*/
	bool SetUpDXGIParameter(
		const std::string& window_class_name,
		DXGI_SWAP_CHAIN_DESC&out_desc
	);


	/**
	* @brief RenderTargetViewの作成
	*/
	bool CreateRenderTargetView();


	/**
	* @brief DepthStencilViewの作成(ステンシルと深度値の保持クラス)
	*/
	bool CreateDepthAndStencilView(
		const std::string& window_class_name
	);


	/**
	* @brief ビューポートの設定
	*/
	bool SetUpViewPort(
		const std::string& window_class_name
	);

private:

	ComPtr<ID3D11Device>mp_device;

	/**
	* @brief DeviceContextのInterface@n
	* Contextは２種類あり、描画命令の実行タイミングが変わる@n
	* ・ImmediateContext@n
	* 　１つだけ作成できるContext@n
	* 　このContextで実行した描画命令はすぐにGPUへ発行される@n
	* ・DeferredContext@n
	* 　このContextで実行した描画命令はコマンドリストへ追加され、@n
	* 　コマンドリスト実行命令を使うことで開始される@n
	*/
	ComPtr<ID3D11DeviceContext>mp_context;

	//! SwapChainのInterface
	ComPtr<IDXGISwapChain>mp_swap_chain;

	//! RenderTargetViewのInterface
	ComPtr<ID3D11RenderTargetView>mp_render_target_view;

	//! ID3D11DepthStencilViewを生成するためのテクスチャ
	ComPtr<ID3D11Texture2D>mp_depth_stencil_texture;

	//! DepthStencilViewのInterface
	ComPtr<ID3D11DepthStencilView>mp_depth_stencil_view;

	//! ウィンドウモード
	bool m_is_window_mode;
};


#endif
