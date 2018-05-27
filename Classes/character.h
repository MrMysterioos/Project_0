#pragma once
#include "Actor.h"

USING_NS_CC;

class Character : public Actor {
protected:
	int _healthPoints;
	float _speed;
	int _attackPower;

	virtual bool init();

};