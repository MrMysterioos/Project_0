#include "ObjectManager.h"

USING_NS_CC;

static ObjectManager* _objectManager = nullptr;

ObjectManager* ObjectManager::getInstance() {

	if (!_objectManager) {
		_objectManager = new (std::nothrow) ObjectManager();
		_objectManager->init();
	}

	return _objectManager;
}

void ObjectManager::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(_objectManager);
}

bool ObjectManager::init() {



	return true;
}

