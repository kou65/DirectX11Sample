#ifndef UN_KNOWN_H_
#define UN_KNOWN_H_


// Windows�W��IUnknown�w�b�_�[
#include<Unknwn.h>


/**
* @brief �Ǝ��A���m�E���N���X
*/
class UnKnown : public IUnknown {
public:


	/**
	* @brief �C���^�[�t�F�[�X�v��
	*/
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) {
		return S_FALSE;
	}


	/**
	* @brief �Q�ƃJ�E���^����
	*/
	virtual unsigned long STDMETHODCALLTYPE AddRef() {
		return ++m_dw_ref;
	}


	/**
	* @brief �Q�ƃJ�E���^����
	*/
	virtual ULONG STDMETHODCALLTYPE Release()
	{
		// �Q�ƃJ�E���g��0�ɂȂ����玩������
		if (--m_dw_ref == 0)
		{
			delete this;
			return 0;
		}

		return m_dw_ref;
	}


protected:

	UnKnown() {

		// �������͎Q�ƃJ�E���g1
		m_dw_ref = 1;

	}

	virtual ~UnKnown() {};


protected:

	//! �Q�ƃJ�E���^�[
	unsigned long m_dw_ref;

};

#endif
