#pragma once

#include "cocos2d.h"

USING_NS_CC;

struct ObjectInfo {
	std::string name, spriteName;
	std::map<std::string, std::string> animationNames;
};

struct CharInfo : public ObjectInfo {
	int health, speed, damage, level, experience;
	std::string team;
};

struct ContInfo : public ObjectInfo {
	
};

struct FireInfo : public ObjectInfo {
};

struct ArtifactInfo : public ObjectInfo {
};