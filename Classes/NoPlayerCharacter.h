#pragma once

#include "Character.h"

USING_NS_CC;

class NoPlayerCharacter : public Character {
public:
	static NoPlayerCharacter *create(ObjectInfo);

	bool setBehavior(Behavior);

private:
	NoPlayerCharacter();

	bool init(ObjectInfo);

	//void update(float) override;

	Team _team;
	std::string _name;

	enum State {idle, walk, run} _state;
};