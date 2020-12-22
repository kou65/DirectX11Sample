#include"WindowsSystem.h"
#include"../IOFunction/IOFunction.h"



namespace WindowsSystem {


	bool ProcessMessage() {

		// メッセージ受け取り用構造体
		MSG msg;

		while (PeekMessage(
			&msg,           // 取得メッセージ
			NULL,           // ウィンドウハンドル(ここはNULLにしないと終了しなかった)
			0,              // 取得メッセージの最大値
			0,			    // 取得メッセージの最小値
			PM_REMOVE		// 取得メッセージの削除オプション
		))
		{
			// 文字列入力系を受け取る
			TranslateMessage(&msg);
			// ウィンドウプロシージャを呼ぶ(重要)
			DispatchMessage(&msg);

			// 終了メッセージの時falseを返す(WM_QUITはスレッド用)
			if (msg.message == WM_QUIT || msg.message == WM_NCDESTROY) {

				return false;
			}

			break;
		}

		// メッセージ送信終了
		return true;
	}


	void TextMessageBox(const std::string& string) {

		MessageBoxA(NULL, string.c_str(), NULL, NULL);
	}


	void OutputDebugLog(const std::string& string) {

		std::wstring wstr;
		Utility::IOFunction::ToWString1(string,wstr);

		OutputDebugString(wstr.c_str());
	}


	void OutputDebugLogLiteral(const std::string& string) {

		OutputDebugStringA(string.c_str());
	}

}