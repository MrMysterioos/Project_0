#pragma once
#include "Actor.h"

USING_NS_CC;

class Character : protected Actor {
protected:
	int _heathlPoints;
	float _speed;
	int _attactPower;

	virtual bool initWithBehavior(Behavior* behavior);
public:
};