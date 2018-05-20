#include "NoPlayerCharacter.h"

USING_NS_CC;

NoPlayerCharacter::NoPlayerCharacter() {};

NoPlayerCharacter *NoPlayerCharacter::create(ObjectInfo objInfo) {
	NoPlayerCharacter *_char = new (std::nothrow) NoPlayerCharacter();
	if (_char && _char->init(objInfo))
	{
		_char->autorelease();
		return _char;
	}
	CC_SAFE_DELETE(_char);
	return nullptr;
}

bool NoPlayerCharacter::init(ObjectInfo objInfo) {

	_objInfo = objInfo;

	_healthPoints			= atoi(_objInfo.getAttribute("health").c_str());
	_speed					= atoi(_objInfo.getAttribute("speed").c_str());
	_attackPower			= atoi(_objInfo.getAttribute("damage").c_str());

	std::string resSource	= _objInfo.getAttribute("animation_set");
	_animationSet = AnimationSet::create(resSource);

	Sprite* _sprite = Sprite::create();
	_sprite->setContentSize(Size(64, 64));
	NoPlayerCharacter::addChild(_sprite);

	Animation *_animation = _animationSet->getAnimation("idle");
	Animate *_animate = Animate::create(_animation);
	_sprite->runAction(RepeatForever::create(_animate));

	return true;
}

bool NoPlayerCharacter::setBehavior(Behavior behavior) {
	_team = behavior.team;
	_name = behavior.name;

	return true;
}