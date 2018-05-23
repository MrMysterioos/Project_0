#pragma once

#include "cocos2d.h"
#include "PauseMenu.h"

using namespace cocos2d;

/**
* @brief Абстрактный класс для всех игровых сцен
*
* Класс GameScene включает в себя вызов паузы, что должно быть в каждой сцене.
*/
class GameScene : public cocos2d::Scene {
public:

	/**
	* @brief Метод для создания сцены
	*
	*/
	static cocos2d::Scene * createScene();

	/**
	* @brief Метод инициализации GameScene
	*
	*/
	virtual bool init() override;

	/**
	* @brief Метод, который срабатывает при нажатии на кнопку
	*
	*/
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	/**
	* @brief Метод, который срабатывает при отпускании кнопки
	*
	*/
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	/**
	* @brief Метод, закрывающий приложение
	*
	*/
	virtual void menuCloseCallback(cocos2d::Ref * pSender);

	/**
	* @brief Метод вызывается на каждой итерации игрового цикла
	*
	*/
	virtual void update(float dt) = 0;
};

int getNumberFromExpression(const std::string & s);

const std::string getStringFromInt(int number);

const std::string getReturnScene(const std::string & s);