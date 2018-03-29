#pragma once

#include "cocos2d.h"
#include "ObjectManager.h"

class Actor: public Node {
protected:
	Sprite* _sprite; //спрайт будет у всех наследников класса
	std::map<std::string, std::string> _animations;	//map анимаций
public:
	virtual void interaction() = 0;	//абстрактная функция взаимодействия
};