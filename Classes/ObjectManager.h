#pragma once

#include "cocos2d.h"

USING_NS_CC;

struct ObjectTemplate {
	std::string spriteName;
	std::map<std::string, std::string> animationNames;
};

struct CharacterTemplate : public ObjectTemplate {
	int health, speed, damage;
};

struct ContainerTemplate : public ObjectTemplate {
	std::vector<std::string> loot;
};

struct CampfireTemplate : public ObjectTemplate {
};

struct ArtifactTemplate : public ObjectTemplate {
};

class ObjectManager : public Ref {
public:
	
	static ObjectManager* getInstance();

	static void destroyInstance();
	
	bool init();

	void addCharacterTemplate(std::string key, CharacterTemplate temp)
	{
		_characters.insert(std::pair<std::string, CharacterTemplate>(key, temp));
	}

	void addContainerTemplate(std::string key, ContainerTemplate temp)
	{
		_containers.insert(std::pair<std::string, ContainerTemplate>(key, temp));
	}

	void addCampfireTemplate(std::string key, CampfireTemplate temp)
	{
		_campfires.insert(std::pair<std::string, CampfireTemplate>(key, temp));
	}

	CharacterTemplate getCharacterTemplate(std::string key)
	{ return _characters.at(key); }
	ContainerTemplate getContainerTemplate(std::string key)
	{ return _containers.at(key); }
	CampfireTemplate getCampfireTemplate(std::string key)
	{ return _campfires.at(key); }

private:

	std::map<std::string, CharacterTemplate>  _characters;
	std::map<std::string, ContainerTemplate>  _containers;
	std::map<std::string, CampfireTemplate>  _campfires;

};