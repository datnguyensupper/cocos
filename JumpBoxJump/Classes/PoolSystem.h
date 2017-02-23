#pragma once
#include "cocos2d.h"

class PoolSystem;
class PoolObject
{
protected:
	PoolSystem* system;
public:
	virtual ~PoolObject();
	virtual void active() {};
	virtual void deactive() {};

	friend class PoolSystem;
};

class PoolSystem
{
private:
	int currentIndex;
	std::function<PoolObject*()> funcInit;
	std::vector<PoolObject*> pool;
	PoolSystem(const std::function<PoolObject*()>& funcInit,
		int initAmount);
public:
	~PoolSystem();

	PoolObject* spawn();
	void destroy(PoolObject* obj);

	void releaseAllObject();

	friend class CPoolManager;
};

class CPoolManager
{
private:
	std::map<std::string, PoolSystem*> map;
public:
	/** Returns the shared instance of the CPoolManager.
	* @return The instance of the CPoolManager.
	*/
	static CPoolManager* getInstance();

	PoolSystem* createSystem(
		const std::string& name, 
		const std::function<PoolObject*()>& funcInit,
		int initAmount = 0);
	PoolSystem* getSystem(const std::string& name) const;
	void releaseSystem(const std::string& name);
	void releaseAllSystem();

	void release();
};
