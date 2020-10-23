#ifndef VIEW_H_
#define VIEW_H_


#include<wrl.h>
#include<d3d11.h>
#include<map>
#include<string>


//! DirectX�ł̃X�}�[�g�|�C���^
using namespace Microsoft::WRL;


/**
* @class ViewManager
* @brief DirectX11��View�n���Ǘ�����N���X
*/
class ViewManager {
public:

	/** @define �ŏ���DEVICE�p */
	const std::string DEVICE_RENDER_TARGET_VIEW = "DeviceView";

public:


	/**
	* @brief �����_�[�^�[�Q�b�g�쐬
	*/
	bool CreateRenderTargetView(
		const std::string& view_name
	);


	/**
	* @brief �N���C�A���g�T�C�Y�̐[�x�X�e���V���r���[�쐬
	*/
	bool CreateClientSizeDepthStencilView(
		const std::string& window_class_name
	);


	/**
	* @brief �[�x�X�e���V���쐬
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
	* @brief ���
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


	//! �����_�[�^�[�Q�b�g�r���[���Ǘ�
	std::map<std::string, ComPtr<ID3D11RenderTargetView>>
		mp_render_target_view_list;

	//! �X�e���V���r���[�̃��X�g���Ǘ�
	std::map<std::string, ComPtr<ID3D11DepthStencilView>>
		mp_depth_stencil_view_list;

	//! ID3D11DepthStencilView�𐶐����邽�߂̃e�N�X�`��
	std::map<std::string, ComPtr<ID3D11Texture2D>>
		mp_depth_stencil_texture_list;
};

#endif
