#include "cocos2d.h"
#include "ObjectManager.h"

class Actor: public Node {
protected:
	Sprite* _sprite; //спрайт будет у всех наследников класса
	Map<std::string, Animation*> _animationsMap; //map анимаций
	Animate* _animate; // анимации
	virtual void interaction() = 0;	//абстрактная функция взаимодействия

	bool initWithBehavior(Behavior*);	//эта функция будет одинаковой у всех наследников
};