#pragma once

#include "cocos2d.h"
#include "PauseMenu.h"

using namespace cocos2d;

/**
* @brief ����������� ����� ��� ���� ������� ����
*
* ����� GameScene �������� � ���� ����� �����, ��� ������ ���� � ������ �����.
*/
class GameScene : public cocos2d::Scene {
public:

	/**
	* @brief ����� ��� �������� �����
	*
	*/
	static cocos2d::Scene * createScene();

	/**
	* @brief ����� ������������� GameScene
	*
	*/
	virtual bool init() override;

	/**
	* @brief �����, ������� ����������� ��� ������� �� ������
	*
	*/
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	/**
	* @brief �����, ������� ����������� ��� ���������� ������
	*
	*/
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	/**
	* @brief �����, ����������� ����������
	*
	*/
	virtual void menuCloseCallback(cocos2d::Ref * pSender);

	/**
	* @brief ����� ���������� �� ������ �������� �������� �����
	*
	*/
	virtual void update(float dt) = 0;
};

int getNumberFromExpression(const std::string & s);

const std::string getStringFromInt(int number);

const std::string getReturnScene(const std::string & s);