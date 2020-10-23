#include"Window.h"


Window::Window(
	const std::string& class_name,
	const std::string& title_name,
	const uint& width_size,
	const uint& height_size
) {

	m_class_name = class_name;
	m_title_name = title_name;
	m_width_size = width_size;
	m_height_size = height_size;
}


LRESULT CALLBACK Window::WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}

	return 0;
}


bool Window::Create()
{
	if (EntryWindowClass() == false)
	{
		return false;
	}


	// ウィンドウ作成
	HWND window_handle = CreateWindowA(
		m_class_name.c_str(),
		m_title_name.c_str(),
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
		CW_USEDEFAULT,
		0,
		m_width_size,
		m_height_size,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	if (window_handle == NULL)
	{
		return false;
	}

	ResizeWindow(window_handle);

	return true;
}


bool Window::EntryWindowClass()
{

	// マルチバイト文字にする
	WNDCLASSEXA window_class = {
		sizeof(WNDCLASSEX),				// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,		// クラスのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 補助メモリ
		0,								// 補助メモリ
		GetModuleHandle(NULL),			// このプログラムのインスタンスハンドル
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),// アイコン画像
		LoadCursor(NULL, IDC_ARROW),	// カーソル画像
		NULL,							// 背景ブラシ(背景色)
		NULL,							// メニュー名
		m_class_name.c_str(),		    // クラス名									
		NULL							// 小さいアイコン
	};

	// 構造体の登録
	if (RegisterClassExA(&window_class) == 0)
	{
		return false;
	}

	return true;
}


void Window::ResizeWindow(HWND window_handle)
{
	RECT window_rect;
	RECT client_rect;

	GetWindowRect(window_handle, &window_rect);
	GetClientRect(window_handle, &client_rect);

	// フレームサイズ
	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	SetWindowPos(window_handle, 
		NULL, CW_USEDEFAULT, 0, 
		m_width_size,
		m_height_size,
		SWP_NOMOVE);

	ShowWindow(window_handle, SW_SHOW);
	UpdateWindow(window_handle);
}


std::string Window::GetWindowName() {
	return m_class_name;
}