#ifndef UN_KNOWN_H_
#define UN_KNOWN_H_


// Windows標準IUnknownヘッダー
#include<Unknwn.h>


/**
* @brief 独自アンノウンクラス
*/
class UnKnown : public IUnknown {
public:


	/**
	* @brief インターフェース要求
	*/
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) {
		return S_FALSE;
	}


	/**
	* @brief 参照カウンタ増加
	*/
	virtual unsigned long STDMETHODCALLTYPE AddRef() {
		return ++m_dw_ref;
	}


	/**
	* @brief 参照カウンタ減少
	*/
	virtual ULONG STDMETHODCALLTYPE Release()
	{
		// 参照カウントが0になったら自動消去
		if (--m_dw_ref == 0)
		{
			delete this;
			return 0;
		}

		return m_dw_ref;
	}


protected:

	UnKnown() {

		// 生成時は参照カウント1
		m_dw_ref = 1;

	}

	virtual ~UnKnown() {};


protected:

	//! 参照カウンター
	unsigned long m_dw_ref;

};

#endif
