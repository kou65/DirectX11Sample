
#ifndef SINGLETON_TEMPLATE_H_
#define SINGLETON_TEMPLATE_H_



// ここに使用クラスが入る
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

	// 隠しコンストラクタ
	Singleton() {}

	~Singleton() {}

private:

	// 実際にfriendにして開示しないと使用できない
	static T* ptr_instance;
};


template <class T>

// nullptrで初期化しておく
T* Singleton<T>::ptr_instance = nullptr;

#endif