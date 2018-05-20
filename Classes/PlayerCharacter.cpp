#include "PlayerCharacter.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter() {};

PlayerCharacter *PlayerCharacter::create(ObjectInfo objInfo) {
	PlayerCharacter *_char = new (std::nothrow) PlayerCharacter();
	if (_char && _char->init(objInfo))
	{
		_char->autorelease();
		return _char;
	}
	CC_SAFE_DELETE(_char);
	return nullptr;
}

bool PlayerCharacter::init(ObjectInfo objInfo) {

	_objInfo = objInfo;

	_healthPoints			= atoi(_objInfo.getAttribute("health").c_str());
	_speed					= atoi(_objInfo.getAttribute("speed").c_str());
	_attackPower			= atoi(_objInfo.getAttribute("damage").c_str());

	std::string resSource	= _objInfo.getAttribute("animation_set");
	_animationSet = AnimationSet::create(resSource);

	Sprite* _sprite = Sprite::create();
	_sprite->setContentSize(Size(64, 64));
	PlayerCharacter::addChild(_sprite);

	changeState(idle);

	_team = FRIEND;
	_name = "Player";

	return true;
}

void PlayerCharacter::setWay(std::vector<Vec2> *way) {
	MoveBy *move;
	while (way != nullptr) {
		switch (int(way->back().x) - int(getPositionInTile().x)) {
		case 1: {
			move = MoveBy::create(5 / _speed, Vec2(tileSize, 0));
			_way.pushBack(move);
			way->pop_back();
			continue;
		}
		case -1: {
			move = MoveBy::create(5 / _speed, Vec2(-tileSize, 0));
			_way.pushBack(move);
			way->pop_back();
			continue;
		}
		case 0: {
			switch (int(way->back().y) - int(getPositionInTile().y)) {
			case 1: {
				move = MoveBy::create(5 / _speed, Vec2(0, tileSize));
				_way.pushBack(move);
				way->pop_back();
				continue;
			}
			case -1: {
				move = MoveBy::create(5 / _speed, Vec2(0, -tileSize));
				_way.pushBack(move);
				way->pop_back();
				continue;
			}
			}
		}
		}
	}
	
	moving();
}

void PlayerCharacter::update(float dt) {
	//Node::
}

void PlayerCharacter::moving() {
	Sequence *move = Sequence::create(_way);
	this->runAction(move);

	scheduleUpdate();
}

void PlayerCharacter::changeState(State newState) {
	if (_state != newState) {
		switch (newState) {
		case idle: {
			_sprite->stopAllActions();
			Animation *_animation = _animationSet->getAnimation("idle");
			Animate *_animate = Animate::create(_animation);
			_sprite->runAction(RepeatForever::create(_animate));
			_state = idle;
			break;
		}
		case walk: {
			_sprite->stopAllActions();
			Animation *_animation = _animationSet->getAnimation("walk");
			Animate *_animate = Animate::create(_animation);
			_sprite->runAction(RepeatForever::create(_animate));
			_state = walk;
			break;
		}
		case run: {
			_sprite->stopAllActions();
			Animation *_animation = _animationSet->getAnimation("run");
			Animate *_animate = Animate::create(_animation);
			_sprite->runAction(RepeatForever::create(_animate));
			_state = run;
			break;
		}
		}
	}
}

void PlayerCharacter::goTo(Vec2 where) {
	auto parent = this->getParent();
	auto scene = dynamic_cast<Scene*> (parent);
}