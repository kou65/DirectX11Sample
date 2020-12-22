#ifndef KEY_BORAD_H_
#define KEY_BORAD_H_

#define NOMINMAX
#include <Windows.h>


/*
キーボード入力処理を支援するシングルトンクラス

◆注意事項
1. ウィンドウプログラムで動作し、コマンドラインプログラムでは動作しない。
2. ウィンドウが非アクティブの場合（選択されていない場合）は検知しない。
3. 毎フレームupdate関数を一回だけ呼ぶ必要がある。
（多重に呼び出した場合はpressとreleaseが正常に動作しない。）

◆使用例
Key& kb = Key::GetInterface();

while(1) {
kb.update();

if (kb.on(VK_SPACE)) {
// スペースキーが押されている間、ずっと実行される。
}

if (kb.press(VK_LBUTTON)) {
// 右クリックされた瞬間、一度だけ実行される。
}

if (kb.release('A')) {
// Aキーが離された瞬間、一度だけ実行される。
}
}
*/
class Key {
public:


	static Key& GetInterface() {
		static Key kb;
		return kb;
	}

	void Update();

	bool Pushing(int nVirtKey) const;
	bool Push(int nVirtKey) const;
	bool Exit(int nVirtKey) const;


private:



	/**
	* @brief デフォルトコンストラクタ
	*/
	Key();


	/**
	* @brief コピーコンストラクタ禁止
	*/
	Key(const Key&) = delete;


	/**
	* @brief ビット演算で排他かどうか調べる
	*/
	inline bool TestBit(const BYTE k) const;


private:

	//! キーリスト
	BYTE m_key_list[2][256] = {};

};


/*

マウスキー

VK_RBUTTOM
VK_LBUTTOM
VK_MBUTTOM

*/

#endif