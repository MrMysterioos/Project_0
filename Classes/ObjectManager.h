#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;

class ObjectManager : public Ref {
public:
	
	static ObjectManager* getInstance();

	static void destroyInstance();
	
	bool init();

	void addCharacterTemplate(std::string key, CharInfo temp)
	{
		_characters.insert(std::pair<std::string, CharInfo>(key, temp));
	}

	void addContainerTemplate(std::string key, ContInfo temp)
	{
		_containers.insert(std::pair<std::string, ContInfo>(key, temp));
	}

	void addCampfireTemplate(std::string key, FireInfo temp)
	{
		_campfires.insert(std::pair<std::string, FireInfo>(key, temp));
	}

	CharInfo getCharacterTemplate(std::string key)
	{ return _characters.at(key); }
	ContInfo getContainerTemplate(std::string key)
	{ return _containers.at(key); }
	FireInfo getCampfireTemplate(std::string key)
	{ return _campfires.at(key); }

private:

	std::map<std::string, CharInfo>  _characters;
	std::map<std::string, ContInfo>  _containers;
	std::map<std::string, FireInfo>  _campfires;

};