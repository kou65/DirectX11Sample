#ifndef WINDOW_H_
#define WINDOW_H_

#include<Windows.h>
#include<string>

/*実装すること

Windowの作成

*/

//! unsigned int をuintとして定義
typedef unsigned int uint;

/**
* @class Window
* @brief ウィンドウ作成クラス
*/
class Window{
public:

	
	/**
	* @brief コンストラクタ
	* @param[in] title タイトル名
	* @param[in] width クライアント領域横のサイズ
	* @param[in] height クライアント領域縦のサイズ
	*/
	Window(
		const std::string&class_name,
		const std::string&title_name,
		const uint& width_size = 1920,
		const uint& height_size = 1080
	);


	/**
	* @brief ウィンドウプロシージャ
	* @param[in] window_handle イベントが発生したウィンドウのハンドル
	* @param[in] message_id イベントメッセージ
	* @param[in] wparam イベント情報
	* @param[in] lparam イベント情報
	* @return メッセージ処理結果
	*/
	static LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam);


	/**
	* @brief ウィンドウ生成関数@n
	* ウィンドウを生成して成功したらtrue、失敗したらfalseを返す
	* @return 生成の成否 成功(true)
	*/
	bool Create();


	/**
	* @brief windowのクラスネームを返す
	* @return std::string クラスネーム
	*/
	std::string GetWindowName();

private:

	/**
	* @brief ウィンドウクラス登録関数@n
	* ウィドウを作成するためのウィンドウクラス情報を登録して成功したらtrue、失敗したらfalseを返す
	* @return 登録の成否 成功(true)
	*/
	bool EntryWindowClass();

	/**
	* @brief ウィドウのリサイズ関数@n
	* 生成後にクライアント領域のサイズにリサイズする
	* @param[in] リサイズ対象となるウィンドウハンドル
	*/
	void ResizeWindow(HWND window_handle);

private:

	//! ウィンドウクラス名
	std::string m_class_name;

	//! タイトル名
	std::string m_title_name;

	//! 横幅
	uint m_width_size;

	//! 縦幅
	uint m_height_size;
};


#endif

/*
ウィンドウ生成で困ったら↓
http
://www-higashi.ist.osaka-u.ac.jp/~k-maeda/vcpp/sec1-3wnddetail.html
*/