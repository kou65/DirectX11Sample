#ifndef COM_PTR_11_H_
#define COM_PTR_11_H_


/*
	ComPtr11の使い方

	インターフェイスを介して生成する場合はToCreate()を使用してください

	やってはいけないこと
	GetPtrで

*/

#define OUTPUT_INTERFACEUSAGE

// COM_DEBUG 1でデバッグモード 0でなし
#define COM_DEBUG 0

#ifdef OUTPUT_INTERFACEUSAGE

	#if COM_DEBUG

	// デバッグ時にファイル出力

	#include <fstream>
	using namespace std;

	#endif

#endif



template<class COM>



/**
* @brief Com専用スマートポインタ
*/
class ComPtr11 {
public:


	/**
	* @brief 暗黙的な型変換を禁止
	* @brief デフォルトコンストラクタ
	* @brief 関数に暗黙型変換代入は出来ない
	* @param[in] p_interface 外部からのインターフェースの受け渡し
	* @param[in] is_add      生成ではなく加算か否か
	*/
	explicit ComPtr11(COM*p_interface = nullptr, bool is_add = false) {

		// 共有の場合はインターフェイスの参照カウンタを増加
		if (p_interface != nullptr && is_add == true) {
			AddRef(p_interface);
		}

		// インターフェースポインタをコピー
		mp_ptr = p_interface;
	}


	/**
	* @brief コピーコンストラクタ
	* @param[in] src コピー元のCom
	*/
	ComPtr11(const ComPtr11&src) {

		// コピー元の参照カウンタを増加
		if (src.mp_ptr) {
			AddRef(src.mp_ptr);
		}

		// コピー
		mp_ptr = src.mp_ptr;
	}


	/**
	* @brief 仮想デストラクタ
	*/
	virtual ~ComPtr11() {

		// 特定の型の関数を呼び出し
		if (mp_ptr) {

			Release(mp_ptr);
			mp_ptr = nullptr;
		}
	}


	/**
	* @brief ptr解放
	*/
	void ReleasePtr() {

		// 特定の型の関数を呼び出し
		if (mp_ptr) {

			Release(mp_ptr);
			mp_ptr = nullptr;
		}
	}


	/**
	* @brief ポインタをそのまま取得
	*/
	COM* GetPtr() {
		return mp_ptr;
	}


	/**
	* @brief ポインタをそのまま取得
	*/
	COM** GetPtrPtr() {
		return &mp_ptr;
	}


	/**
	* @brief インターフェイス生成関数へ流す専用
	*/
	COM** ToCreate() {

		// 自分のインターフェイスを変更することが前提
		if (mp_ptr) {
			Release(mp_ptr);
		}
		return &mp_ptr;
	}


	/**
	* @brief =代入演算子 明示的なコピー
	*/
	ComPtr11& operator=(const ComPtr11&src) {
		
		// 自分が保持しているインターフェースの参照カウンタを減少
		if (mp_ptr) {
			Release(mp_ptr);
		}

		// コピー元の参照カウンタを増加
		if (src.mp_ptr) {
			AddRef(src.mp_ptr);
		}

		// コピー(新しいポインタを保持する)
		mp_ptr = src.mp_ptr;

		// コピーを渡す
		return (*this);
	}


	/**
	* @brief =代入演算子
	*/
	void operator =(COM* p_interface) {

		// 自分のインターフェイスの参照カウンタを一つ減らす
		if (mp_ptr) {
			Release(mp_ptr);
		}

		// コピー
		mp_ptr = p_interface;
	}


	/**
	* @brief インターフェイスの有無をチェックする時に使用する
	*/
	bool operator == (int value) {

		if (value == (int)mp_ptr) {
			return true;
		}
		return false;
	}


	/**
	* @brief インターフェイスの有無をチェックする時に使用する
	*/
	bool operator != (int value) {

		if (value != (int)mp_ptr) {
			return true;
		}

		return false;
	}

protected:
	

	/**
	* @brief 参照カウンタ増加
	*/
	void AddRef(COM* p_interface){

		#if COM_DEBUG
		// デバッグ版では参照カウントを出力する
		unsigned long c = p_interface->AddRef();
		ofstream ofs;
		ofs.open("DEBUG.txt",ios::app);
		ofs << p_interface << "\t[" << c << "]" << endl;
		ofs.close();
		#else
		p_interface->AddRef();
		#endif
	}
	

	/**
	* @brief 参照カウンタ減少
	*/
	unsigned long Release(COM*p_interface) {


		unsigned long c = p_interface->Release();

		#if COM_DEBUG
		
		ofstream ofs;
		ofs.open("DEBUG.txt",ios::app);
		ofs << p_interface << "\t[" << c << "]" << endl;
		ofs.close();

		#else

		#endif

		return c;
	}

private:


	//! Comのポインタ
	COM*mp_ptr;


};

#endif