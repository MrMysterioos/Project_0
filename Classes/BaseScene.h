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

	TMXTiledMap * _map;

	const int WALL = -1;
	const int BLANK = -2;

	//vectors with position tiles
	int _inc;

	std::vector<Vec2> _startPoints;

	std::vector<Vec2> _way;

	std::vector< std::vector<int> > _path;

	Follow * camera;

	Sprite * _actor; //test
	Vec2 _posActorAt;

	

	float _speed;

	bool setWayCoordinate(Vec2 a, Vec2 b);

	Vec2 convertToCoordinate(Vec2 vec);
};