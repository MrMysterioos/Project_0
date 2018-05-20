#include "Actor.h"

USING_NS_CC;

bool Actor::init() {
	/*ObjectManager* objectManager = ObjectManager::getInstance();
	VisualObject* visualObject = objectManager->getVisualObject(behavior->baseObject->getAttribute("v_obj"));

	_sprite = Sprite::createWithSpriteFrame(visualObject->getSpriteFrame());

	_animationsMap = visualObject->getAnimation();
	_animate = Animate::create(_animationsMap.at("idle"));*/

	_sprite = Sprite::create();
	_sprite->setContentSize(Size(64, 64));

	return true;
}

void Actor::setPositionInTile(Vec2 coord) {
	return this->setPosition(coord * tileSize);
}

Vec2 Actor::getPositionInTile() {
	return Vec2(this->getPosition().x / tileSize, this->getPosition().y /tileSize);
}
