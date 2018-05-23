#pragma once

#include "GameScene.h"
#include "cocos2d.h"

using namespace cocos2d;

class BattleScene : public GameScene {
public:
	static cocos2d::Scene * createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref * pSender);

	void update(float dt);

	CREATE_FUNC(BattleScene);
private:
	int _actID;
};