
#ifndef SINGLETON_TEMPLATE_H_
#define SINGLETON_TEMPLATE_H_



// �����Ɏg�p�N���X������
template<class T>

class Singleton {
public:

	static void CreateInstance()
	{

		if (IsNull() == true) { ptr_instance = new T(); }

	}

	static void DestroyInstance()

	{

		if (IsNull() == false) { delete ptr_instance; }

	}

	static bool IsNull()

	{

		return ptr_instance == nullptr;

	}

	static T* GetInstance()

	{
		return ptr_instance;
	}

protected:

	// �B���R���X�g���N�^
	Singleton() {}

	~Singleton() {}

private:

	// ���ۂ�friend�ɂ��ĊJ�����Ȃ��Ǝg�p�ł��Ȃ�
	static T* ptr_instance;
};


template <class T>

// nullptr�ŏ��������Ă���
T* Singleton<T>::ptr_instance = nullptr;

#endif