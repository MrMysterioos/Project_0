#pragma once

#include "cocos2d.h"

USING_NS_CC;

struct ObjectInfo {
	std::string spriteName;
	std::map<std::string, std::string> animationNames;
};

struct CharInfo : public ObjectInfo {
	int health, speed, damage, level, experience;
};

struct ContInfo : public ObjectInfo {
	std::vector<std::string> loot;
};

struct FireInfo : public ObjectInfo {
};

struct ArtifactInfo : public ObjectInfo {
};