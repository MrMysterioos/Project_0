#pragma once

#include "Character.h"

USING_NS_CC;

class PlayerCharacter : public Character {
public:
	static PlayerCharacter *create(ObjectInfo);

	void setWay(std::vector<Vec2>*);

private:
	enum State { idle, walk, run } _state;

	PlayerCharacter();

	bool init(ObjectInfo);

	void goTo(Vec2);

	void moving();

	void update(float) override;

	void changeState(State);

	Team _team;
	std::string _name;

	Vector<FiniteTimeAction*> _way;
};