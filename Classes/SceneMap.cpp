#include "SceneMap.h"

using namespace cocos2d;

SceneMap SceneMap::createSceneMap(const std::string & nameMap) {
	_map = TMXTiledMap::create(nameMap);
	return this;
}