#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class PauseMenu : public Layer {
public:
	static Layer * createLayer();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	CREATE_FUNC(PauseMenu);
};
