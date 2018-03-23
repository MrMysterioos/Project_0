#include "GameInfo.h"

static GameInfo* _gameInfo = nullptr;

GameInfo* GameInfo::getInstance() {

	if (!_gameInfo) {
		_gameInfo = new (std::nothrow) GameInfo();
		_gameInfo->init();
	}

	return _gameInfo;
}

void GameInfo::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(_gameInfo);
}

bool GameInfo::init() {



	return true;
}

bool GameInfo::initWithFile(std::string file) {

	return true;
}