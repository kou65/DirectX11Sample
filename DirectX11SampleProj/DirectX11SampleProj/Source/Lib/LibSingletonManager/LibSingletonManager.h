#ifndef SINGLETON_MANAGER_H_
#define SINGLETON_MANAGER_H_
#include"../SingletonTemplate/SingletonTemplate.h"



/**
* @class SingletonManager
* @brief シングルトンを生成削除するクラス
*/
class LibSingletonManager : public Singleton<LibSingletonManager> {
public:

	friend Singleton<LibSingletonManager>;

public:


	/**
	* @brief 生成
	*/
	void Create();


	/**
	* @brief 削除
	*/
	void DestroyEverything();

private:

	LibSingletonManager() {};
};


#endif
