#ifndef DEVICE_H_
#define DEVICE_H_

#include<d3d11.h>
#include<string>

#pragma comment(lib,"d3d11.lib")

#include<wrl.h>
#include"../SingletonTemplate/SingletonTemplate.h"


//! DirectX�ł̃X�}�[�g�|�C���^
using namespace Microsoft::WRL;


/**
* @class Device
* @brief �f�o�C�X�֌W�̃N���X
*/
class Device {
public:


	/**
	* @brief �e�f�o�C�X�̏�����
	* @return bool ����������=true ���s=false
	*/
	bool Init(
		const std::string&window_class_name,
		bool is_window_mode = true
	);


	/**
	* @brief �e�f�o�C�X�̉��
	*/
	void Release();


	/**
	* @brief �`��J�n
	*/
	void StartRendering();


	/**
	* @brief �`��I��
	*/
	void EndRendering();

private:


	/**
	* @brief �f�o�C�X�ƃX���b�v�`�F�[��(GPU�֑���@�\)�̍쐬
	*/
	bool CreateDeviceAndSwapChain(
		const std::string& window_class_name
	);


	/**
	* @brief �Z�b�g�p�����[�^DXGI
	* @param[in] class_name �E�B���h�E�̃N���X��������
	* @param[out] out_desc DXGI�̃f�X�N���
	*/
	bool SetUpDXGIParameter(
		const std::string& window_class_name,
		DXGI_SWAP_CHAIN_DESC&out_desc
	);


	/**
	* @brief RenderTargetView�̍쐬
	*/
	bool CreateRenderTargetView();


	/**
	* @brief DepthStencilView�̍쐬(�X�e���V���Ɛ[�x�l�̕ێ��N���X)
	*/
	bool CreateDepthAndStencilView(
		const std::string& window_class_name
	);


	/**
	* @brief �r���[�|�[�g�̐ݒ�
	*/
	bool SetUpViewPort(
		const std::string& window_class_name
	);

private:

	ComPtr<ID3D11Device>mp_device;

	/**
	* @brief DeviceContext��Interface@n
	* Context�͂Q��ނ���A�`�施�߂̎��s�^�C�~���O���ς��@n
	* �EImmediateContext@n
	* �@�P�����쐬�ł���Context@n
	* �@����Context�Ŏ��s�����`�施�߂͂�����GPU�֔��s�����@n
	* �EDeferredContext@n
	* �@����Context�Ŏ��s�����`�施�߂̓R�}���h���X�g�֒ǉ�����A@n
	* �@�R�}���h���X�g���s���߂��g�����ƂŊJ�n�����@n
	*/
	ComPtr<ID3D11DeviceContext>mp_context;

	//! SwapChain��Interface
	ComPtr<IDXGISwapChain>mp_swap_chain;

	//! RenderTargetView��Interface
	ComPtr<ID3D11RenderTargetView>mp_render_target_view;

	//! ID3D11DepthStencilView�𐶐����邽�߂̃e�N�X�`��
	ComPtr<ID3D11Texture2D>mp_depth_stencil_texture;

	//! DepthStencilView��Interface
	ComPtr<ID3D11DepthStencilView>mp_depth_stencil_view;

	//! �E�B���h�E���[�h
	bool m_is_window_mode;
};


#endif
