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
	static PlayerCharacter *create(ObjectInfo);
	/*
	* @brief ��������� ��������� � ��������� �����
	*
	* @arguments �������� ���������� ����� ����������
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