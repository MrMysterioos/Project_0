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
	static PlayerCharacter *create();
	/*
	* @brief »нициализаци€ игрового персонажа, загрузка всех его основных параметров.
	*
	* @arguments ObjectInfo персонажа
	*/
	bool init(ObjectInfo playerInfo);
	/*
	* @brief ќтправить персонажа в указанную точку
	*
	* @arguments “айловые координаты точки назначени€
	*/
	void goTo(Vec2);
	/**
	* @brief ‘ункци€ мгновенной остановки перемещени€ персонажа
	*
	*/
	void stopMoving();

private:
	enum State { idle, walk, run } _state;

	PlayerCharacter();

	void update(float) override;

	void changeState(State);

	Team _team;

	std::string _name;

	std::deque<std::pair<MoveTo*, int> > _way;
};