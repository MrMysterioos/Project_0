#pragma once

#include "cocos2d.h"
#include "PauseMenu.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene {
public:

	static cocos2d::Scene * createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref * pSender);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	//CREATE_FUNC(GameScene);

	//void callPauseMenu();
};