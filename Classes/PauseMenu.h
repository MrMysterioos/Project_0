#pragma once

#include "cocos2d.h"

using namespace cocos2d;

/**
* @brief �����, �������������� ���� �����
*
* ����� PauseMenu ���������� ��� ������� �� ������� ESC � ����
*/
class PauseMenu : public Layer {
public:
	static Layer * createLayer();

	virtual bool init();

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(PauseMenu);
	
private:
	void _resumeGame();
};
