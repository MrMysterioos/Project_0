#pragma once

#include "Character.h"

USING_NS_CC;
/**
* @brief ����� ������� �������� �������� ������������ �������� �����������.
* ������������� ����� ������������ ������ ���� ������ ����� ������ ( � ��������� )
*
*/
class PlayerCharacter : public Character {
public:
	/*
	* @brief ������� ����� ��������� ������
	*
	* @return ������ �� ����� ���������
	*/
	static PlayerCharacter *create();
	/*
	* @brief ������������� �������� ���������, �������� ���� ��� �������� ����������.
	*
	* @arguments ObjectInfo ���������
	*/
	bool init(ObjectInfo playerInfo);
	/*
	* @brief ��������� ��������� � ��������� �����
	*
	* @arguments �������� ���������� ����� ����������
	*/
	void goTo(Vec2);
	/**
	* @brief ������� ���������� ��������� ����������� ���������
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