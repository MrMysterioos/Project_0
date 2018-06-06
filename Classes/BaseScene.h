#pragma once

#include "GameScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>
#include <map>
#include "PlayerCharacter.h"

using namespace cocos2d;

/**
* @brief Класс, представляющий собой главную игровую сцену
*
* Данная сцена запускается при нажатии на кнопку Play в главном меню
*/
class BaseScene : public GameScene {
public:
	static cocos2d::Scene * createScene();

	virtual bool init() override;

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) override;

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) override;

	void update(float dt) override;

	void onMouseDown(Event * event);

	/**
	* @brief Получить матрицу карты
	* @return Возвращает целочисленную матрицу tmx карты, где показаны места, по которым можно перемещаться
	*/
	inline const std::vector< std::vector<int> > & getMapMatrix() { return _path; }

	/**
	* @brief Получить размер карты
	* @return Возвращает размер карты в тайлах
	*/
	inline const Size & getMapSize() { return _map->getMapSize(); }

	/**
	* @brief Получить размер тайла
	* @return Возвращает размер тайла в пикселях
	*/
	inline const Size & getTileSize() { return _map->getTileSize() * _map->getScale(); }


	CREATE_FUNC(BaseScene);

private:
	//*********
	//НАРАБОТКИ
	//*********

	void GameOver();

	//инициализирует данные о задании относительно заданного акта
	void _initActScene(int id);

	void _initActByResult(int result);
	void _initActByResult(bool result);
	void _initTasksBattleAct();
	void _initNPC();

	void _updateCamera();

public:
	//константа, обозначающая препятствие на векторе пути перемещения
	const int WALL = 0;
	//константа, обозначающая возможность прохода на векторе пути перемещения
	const int BLANK = 1;

private:
	TMXTiledMap * _map;

	//вектор из координат точек старта в тайл-координатах
	std::vector<Vec2> _startPoints;

	//вектор представления карты в тайл-координатах виде
	std::vector< std::vector<int> > _path;

	PlayerCharacter *_player;

	//*********
	//НАРАБОТКИ
	//*********
	std::vector<std::string> _enemys;
	std::map<std::string, bool> _tasks;
	int _countTasks;

	//это лейбл, который выводит задание
	Label * _labelTask;

	//строка, которая содержит задание
	std::string _task;

	//имя одной из цели, к которой нужно перемещаться
	std::string _typeAct;

	//позиция, к которой нужно передвигаться, чтобы выполнить задание
	Vec2 _posTarget;

	//номер акта в игре
	int _actID;
};