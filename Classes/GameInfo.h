#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;

class GameInfo : public Ref {
public:

	static GameInfo* getInstance();

	static void destroyInstance();

	bool init();

	bool initWithFile(std::string file);

private:

	std::vector<CharInfo> heroes;

};