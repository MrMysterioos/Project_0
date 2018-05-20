#pragma once

#include "GameScene.h"
#include "cocos2d.h"
#include <string>
#include <vector>

using namespace cocos2d;

class BaseScene : public GameScene {
public:
	static cocos2d::Scene * createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref * pSender);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event);

	virtual void onMouseDown(Event * event);

	void update(float dt);

	CREATE_FUNC(BaseScene);
private:
	//функция задания вектора пути перемещения
	//применяется волновой алгоритм
	//применяются два аргумента а - начальная точка, b - конечная
	bool setWayCoordinate(Vec2 a, Vec2 b);

	//функция инициализации вектора представления карты
	void initMapWay();

	//конвертирует из тайл-координат в пиксельную координату
	Vec2 convert(Vec2 vec);

	//функция, которая определяет зашла ли точка from за to
	//где velocity направление, в котором должна двигаться точка
	//используется и для оси x и для оси y по-отдельности
	bool isBelong(int velocity, float from, float to);
private:

	//константа, обозначающая препятствие на векторе пути перемещения
	const int WALL = -1;
	//константа, обозначающая возможность прохода на векторе пути перемещения
	const int BLANK = -2;

	TMXTiledMap * _map;

	//вектор из координат точек старта в тайл-координатах
	std::vector<Vec2> _startPoints;
	
	//вектор пути перемещения в тайл-координатах
	std::vector<Vec2> _way;
	
	//вектор представления карты в тайл-координатах виде
	std::vector< std::vector<int> > _path;



	/************************/
	Sprite * _actor;
	float _speed;

	//позиция персонажа относительно карты в тайл-координатах
	Vec2 _posActorAt;

	//переменная, которая перемещает нас по _way в update()
	int _inc;	

	Sprite * _cameraTarget;
	Follow * _camera;
	
	/****************************/
};