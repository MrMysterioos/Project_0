#pragma once

#include "GameScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>

using namespace cocos2d;
using namespace cocos2d::ui;

class DialogScene : public GameScene {
public:
	static cocos2d::Scene * createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref * pSender);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void onMouseDown(Event * event);

	void setID(int ID);

	void update(float dt);

	CREATE_FUNC(DialogScene);
private:
	std::string _actID;
	Button* button;
};