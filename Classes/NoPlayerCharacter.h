#pragma once

#include "Character.h"

USING_NS_CC;

class NoPlayerCharacter : public Character {
public:
	static NoPlayerCharacter *create();

	bool setBehavior(Behavior);

	bool init(ObjectInfo);

private:
	NoPlayerCharacter();


	//void update(float) override;

	Team _team;
	std::string _name;

	enum State {idle, walk, run} _state;
};