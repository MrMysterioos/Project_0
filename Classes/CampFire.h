#pragma once

#include "Actor.h"

class CampFire : public Actor {
public:
	//CampFire(FireInfo);
	CampFire* createWithName(std::string); // �������� �� �����
	void interaction();	//�������������� � ������� ���������
private:
	Node* _node; // ����� - ��� ����
};