#pragma once

#include "Character.h"

USING_NS_CC;
/**
* @brief  ласс объекты которого €вл€ютс€ управл€емыми игровыми персонажами.
* ≈диновременно может существовать только один объект этого класса ( в доработке )
*
*/
class PlayerCharacter : public Character {
public:
	/*
	* @brief —оздать новый экземпл€р класса
	*
	* @return —сылку на новый экземпл€р
	*/
	static PlayerCharacter *create(ObjectInfo);
	/*
	* @brief ќтправить персонажа в указанную точку
	*
	* @arguments “айловые координаты точки назначени€
	*/
	void goTo(Vec2);

private:
	enum State { idle, walk, run } _state;

	PlayerCharacter();

	bool init(ObjectInfo);

	void update(float) override;

	void changeState(State);

	Team _team;

	std::string _name;

	std::queue<MoveBy*> _way;
};