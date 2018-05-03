#include "Actor.h"

USING_NS_CC;

bool Actor::initWithBehavior(Behavior* behavior) {
	ObjectManager* objectManager = ObjectManager::getInstance();
	VisualObject* visualObject = objectManager->getVisualObject(behavior->baseObject->getAttribute("v_obj"));

	_sprite = Sprite::createWithSpriteFrame(visualObject->getSpriteFrame());

	_animationsMap = visualObject->getAnimation();
	_animate = Animate::create(_animationsMap.at("idle"));

	_sprite->runAction(RepeatForever::create(_animate));

	return true;
}