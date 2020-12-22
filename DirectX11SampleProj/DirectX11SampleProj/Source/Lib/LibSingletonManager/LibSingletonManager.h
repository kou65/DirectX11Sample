#ifndef SINGLETON_MANAGER_H_
#define SINGLETON_MANAGER_H_
#include"../SingletonTemplate/SingletonTemplate.h"



/**
* @class SingletonManager
* @brief �V���O���g���𐶐��폜����N���X
*/
class LibSingletonManager : public Singleton<LibSingletonManager> {
public:

	friend Singleton<LibSingletonManager>;

public:


	/**
	* @brief ����
	*/
	void Create();


	/**
	* @brief �폜
	*/
	void DestroyEverything();

private:

	LibSingletonManager() {};
};


#endif
