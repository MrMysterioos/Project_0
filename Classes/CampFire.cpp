/*#include "CampFire.h"

USING_NS_CC;

CampFire::CampFire() {}

CampFire* CampFire::createWithName(std::string key) {
	CampFire* _campfire = new (std::nothrow) CampFire();
	if (_campfire && initWithName(key))
	{
		_campfire->autorelease();
		return _campfire;
	}
	CC_SAFE_DELETE(_campfire);
	return nullptr;
}

bool CampFire::initWithName(std::string key) {
	FireInfo _info = ObjectManager::getInstance()->getCampfireTemplate(key);
	_sprite = Sprite::createWithSpriteFrameName(_info.spriteName);
	_animates
}*/