#pragma once

#include "cocos2d.h"
#include "ObjectManager.h"

class Actor {
private:
	Sprite* _sprite;
	std::map<std::string, std::string> _animations;
public:
	virtual void interaction() = 0;
};