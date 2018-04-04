#pragma once

#include "cocos2d.h"

USING_NS_CC;

class ObjectInfo : public Ref {
public:
	std::string name, spriteName;
	std::map<std::string, std::string> animationNames;
};

class CharInfo : public ObjectInfo {
public:
	static CharInfo* create(std::string id);

public:
	int health, speed, damage, level, experience;
	std::string team;
};

class ContInfo : public ObjectInfo {
public:
	static ContInfo* create(std::string id);
};

class FireInfo : public ObjectInfo {
public:
	static FireInfo* create(std::string id);
};

class ArtifactInfo : public ObjectInfo {
public:
	static ArtifactInfo* create(std::string id);
};