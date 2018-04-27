#pragma once

#include "Actor.h"

class CampFire : public Actor {
public:
	CampFire* createWithName(std::string); // Создание по имени
	bool initWithName(std::string); //замена присваивания всего-всего в конструкторе (как Кочкин советовал)
	void interaction();	//взаимодействие с другими объектами
private:
	//Sprite* _sprite;
	CampFire();
	CampFire* _campfire;
};