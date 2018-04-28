#pragma once

#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;
enum Team { FRIEND, ENEMY, NEUTRAL };
// один класс для создания всех объектов
class ObjectInfo : public Ref {
public:
	static ObjectInfo* create(tinyxml2::XMLDocument& doc, std::string id);
	bool init(tinyxml2::XMLDocument& doc, std::string id);

	inline std::string getAttribute(std::string key) { return _info.at(key); }

private:
	
	std::map<std::string, std::string> _info;

};
// пользовательский адаптер для IbjectInfo с расширенными параметрами
class Behavior : public Ref {
public:
	static Behavior* create();

public:
	ObjectInfo* baseObject; // иоформация об объекте
	std::string name; // отображаемое имя
	Team team; // команда (друг, враг или нейтральный)
};

