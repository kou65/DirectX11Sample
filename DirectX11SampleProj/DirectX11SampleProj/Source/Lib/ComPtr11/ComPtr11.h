#ifndef COM_PTR_11_H_
#define COM_PTR_11_H_


/*
	ComPtr11�̎g����

	�C���^�[�t�F�C�X����Đ�������ꍇ��ToCreate()���g�p���Ă�������

	����Ă͂����Ȃ�����
	GetPtr��

*/

#define OUTPUT_INTERFACEUSAGE

// COM_DEBUG 1�Ńf�o�b�O���[�h 0�łȂ�
#define COM_DEBUG 0

#ifdef OUTPUT_INTERFACEUSAGE

	#if COM_DEBUG

	// �f�o�b�O���Ƀt�@�C���o��

	#include <fstream>
	using namespace std;

	#endif

#endif



template<class COM>



/**
* @brief Com��p�X�}�[�g�|�C���^
*/
class ComPtr11 {
public:


	/**
	* @brief �ÖٓI�Ȍ^�ϊ����֎~
	* @brief �f�t�H���g�R���X�g���N�^
	* @brief �֐��ɈÖٌ^�ϊ�����͏o���Ȃ�
	* @param[in] p_interface �O������̃C���^�[�t�F�[�X�̎󂯓n��
	* @param[in] is_add      �����ł͂Ȃ����Z���ۂ�
	*/
	explicit ComPtr11(COM*p_interface = nullptr, bool is_add = false) {

		// ���L�̏ꍇ�̓C���^�[�t�F�C�X�̎Q�ƃJ�E���^�𑝉�
		if (p_interface != nullptr && is_add == true) {
			AddRef(p_interface);
		}

		// �C���^�[�t�F�[�X�|�C���^���R�s�[
		mp_ptr = p_interface;
	}


	/**
	* @brief �R�s�[�R���X�g���N�^
	* @param[in] src �R�s�[����Com
	*/
	ComPtr11(const ComPtr11&src) {

		// �R�s�[���̎Q�ƃJ�E���^�𑝉�
		if (src.mp_ptr) {
			AddRef(src.mp_ptr);
		}

		// �R�s�[
		mp_ptr = src.mp_ptr;
	}


	/**
	* @brief ���z�f�X�g���N�^
	*/
	virtual ~ComPtr11() {

		// ����̌^�̊֐����Ăяo��
		if (mp_ptr) {

			Release(mp_ptr);
			mp_ptr = nullptr;
		}
	}


	/**
	* @brief ptr���
	*/
	void ReleasePtr() {

		// ����̌^�̊֐����Ăяo��
		if (mp_ptr) {

			Release(mp_ptr);
			mp_ptr = nullptr;
		}
	}


	/**
	* @brief �|�C���^�����̂܂܎擾
	*/
	COM* GetPtr() {
		return mp_ptr;
	}


	/**
	* @brief �|�C���^�����̂܂܎擾
	*/
	COM** GetPtrPtr() {
		return &mp_ptr;
	}


	/**
	* @brief �C���^�[�t�F�C�X�����֐��֗�����p
	*/
	COM** ToCreate() {

		// �����̃C���^�[�t�F�C�X��ύX���邱�Ƃ��O��
		if (mp_ptr) {
			Release(mp_ptr);
		}
		return &mp_ptr;
	}


	/**
	* @brief =������Z�q �����I�ȃR�s�[
	*/
	ComPtr11& operator=(const ComPtr11&src) {
		
		// �������ێ����Ă���C���^�[�t�F�[�X�̎Q�ƃJ�E���^������
		if (mp_ptr) {
			Release(mp_ptr);
		}

		// �R�s�[���̎Q�ƃJ�E���^�𑝉�
		if (src.mp_ptr) {
			AddRef(src.mp_ptr);
		}

		// �R�s�[(�V�����|�C���^��ێ�����)
		mp_ptr = src.mp_ptr;

		// �R�s�[��n��
		return (*this);
	}


	/**
	* @brief =������Z�q
	*/
	void operator =(COM* p_interface) {

		// �����̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^������炷
		if (mp_ptr) {
			Release(mp_ptr);
		}

		// �R�s�[
		mp_ptr = p_interface;
	}


	/**
	* @brief �C���^�[�t�F�C�X�̗L�����`�F�b�N���鎞�Ɏg�p����
	*/
	bool operator == (int value) {

		if (value == (int)mp_ptr) {
			return true;
		}
		return false;
	}


	/**
	* @brief �C���^�[�t�F�C�X�̗L�����`�F�b�N���鎞�Ɏg�p����
	*/
	bool operator != (int value) {

		if (value != (int)mp_ptr) {
			return true;
		}

		return false;
	}

protected:
	

	/**
	* @brief �Q�ƃJ�E���^����
	*/
	void AddRef(COM* p_interface){

		#if COM_DEBUG
		// �f�o�b�O�łł͎Q�ƃJ�E���g���o�͂���
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
	* @brief �Q�ƃJ�E���^����
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


	//! Com�̃|�C���^
	COM*mp_ptr;


};

#endif