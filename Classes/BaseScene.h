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
	//������� ������� ������� ���� �����������
	//����������� �������� ��������
	//����������� ��� ��������� � - ��������� �����, b - ��������
	bool setWayCoordinate(Vec2 a, Vec2 b);

	//������� ������������� ������� ������������� �����
	void initMapWay();

	//������������ �� ����-��������� � ���������� ����������
	Vec2 convert(Vec2 vec);

	//�������, ������� ���������� ����� �� ����� from �� to
	//��� velocity �����������, � ������� ������ ��������� �����
	//������������ � ��� ��� x � ��� ��� y ��-�����������
	bool isBelong(int velocity, float from, float to);
private:

	//���������, ������������ ����������� �� ������� ���� �����������
	const int WALL = -1;
	//���������, ������������ ����������� ������� �� ������� ���� �����������
	const int BLANK = -2;

	TMXTiledMap * _map;

	//������ �� ��������� ����� ������ � ����-�����������
	std::vector<Vec2> _startPoints;
	
	//������ ���� ����������� � ����-�����������
	std::vector<Vec2> _way;
	
	//������ ������������� ����� � ����-����������� ����
	std::vector< std::vector<int> > _path;



	/************************/
	Sprite * _actor;
	float _speed;

	//������� ��������� ������������ ����� � ����-�����������
	Vec2 _posActorAt;

	//����������, ������� ���������� ��� �� _way � update()
	int _inc;	

	Sprite * _cameraTarget;
	Follow * _camera;
	
	/****************************/
};