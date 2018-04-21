#pragma once
#include "cocos2d.h"
#include <string>

class SceneMap {
public:

	static SceneMap createSceneMap(const std::string & nameMap);

	inline cocos2d::TMXTiledMap * getMap() { return _map; }

private:
	cocos2d::TMXTiledMap * _map;
};