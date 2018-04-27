#pragma once

#include "Actor.h"

class CampFire : public Actor {
public:
	CampFire* createWithName(std::string); // �������� �� �����
	bool initWithName(std::string); //������ ������������ �����-����� � ������������ (��� ������ ���������)
	void interaction();	//�������������� � ������� ���������
private:
	//Sprite* _sprite;
	CampFire();
	CampFire* _campfire;
};