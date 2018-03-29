#pragma once

#include "Actor.h"

class CampFire : public Actor {
public:
	//CampFire(FireInfo);
	CampFire* createWithName(std::string); // Создание по имени
	void interaction();	//взаимодействие с другими объектами
private:
	Node* _node; // костёр - это узел
};