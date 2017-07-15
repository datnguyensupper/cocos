#include "PoolSystem.h"

PoolObject::PoolObject()
{
	this->retain();
}

PoolObject::~PoolObject()
{
}

PoolSystem::PoolSystem(const std::function<PoolObject*()>& funcInit,
	int initAmount)
{
	if (!funcInit) {
		return;
	}
	this->currentIndex = 0;
	this->funcInit = funcInit;
	for (int i = 0; i < initAmount; ++i) {
		auto obj = this->funcInit();
		obj->system = this;
		this->pool.push_back(obj);
	}
	this->currentIndex = initAmount;
}
PoolSystem::~PoolSystem()
{
	this->releaseAllObject();
	this->funcInit = nullptr;
}
PoolObject * PoolSystem::spawn(){
	PoolObject* obj;
	if (this->currentIndex > 0) {
		this->currentIndex--;
		obj = this->pool[this->currentIndex];
		this->pool[this->currentIndex] = nullptr;
	}
	else {
		obj = this->funcInit();
		obj->system = this;
		this->pool.push_back(obj);
	}
	if (obj) {
		obj->active();
	}
	return obj;
}
void PoolSystem::destroy(PoolObject * obj)
{
	if (obj) {
		obj->deactive();
		this->pool[this->currentIndex++] = obj;
	}
}
void PoolSystem::releaseAllObject()
{
	for (auto obj : this->pool) {
		CC_SAFE_RELEASE_NULL(obj);
	}
	this->pool.clear();
}

static CPoolManager *_sharedPoolManager = nullptr;
CPoolManager * CPoolManager::getInstance()
{
	if (!_sharedPoolManager)
	{
		_sharedPoolManager = new (std::nothrow) CPoolManager();
	}
	return _sharedPoolManager;
}

PoolSystem* CPoolManager::createSystem(
	const std::string& name, 
	const std::function<PoolObject*()>& funcInit,
	int initAmount)
{
	this->map[name] = new PoolSystem(funcInit, initAmount);
	return this->map[name];
}

PoolSystem * CPoolManager::getSystem(const std::string& name) const
{
	if (this->map.find(name) != this->map.end()) {
		return this->map.at(name);
	}
	return nullptr;
}

void CPoolManager::releaseSystem(const std::string& name)
{
	if (this->map.find(name) != this->map.end()) {
		CC_SAFE_DELETE(this->map[name]);
		this->map.erase(name);
	}
}

void CPoolManager::releaseAllSystem()
{
	for (auto system : map) {
		CC_SAFE_DELETE(system.second);
	}
	this->map.clear();
}

void CPoolManager::release()
{
	this->releaseAllSystem();
	CC_SAFE_DELETE(_sharedPoolManager);
}
