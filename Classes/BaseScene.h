#pragma once

#include "GameScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>
#include <map>

using namespace cocos2d;

/**
* @brief �����, �������������� ����� ������� ������� �����
*
* ������ ����� ����������� ��� ������� �� ������ Play � ������� ����
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
	* @brief �������� ������� �����
	* @return ���������� ������������� ������� tmx �����, ��� �������� �����, �� ������� ����� ������������
	*/
	inline const std::vector< std::vector<int> > & getMapMatrix() { return _path; }


	CREATE_FUNC(BaseScene);

private:
	//*********
	//���������
	//*********

	void GameOver();

	//�������������� ������ � ������� ������������ ��������� ����
	void _initActScene(int id);

	void _initActByResult(int result);
	void _initActByResult(bool result);
	void _initTasksBattleAct();


	//*********
	//��������������� ���
	//P.S. ����� ������ ����� ������
	//*********

	void d_onMouseDown(Event * event);

	void d_update(float dt);

	void d_initActor();

	//������� ������� ������� ���� �����������
	//����������� �������� ��������
	//����������� ��� ��������� � - ��������� �����, b - ��������
	bool d_setWayCoordinate(Vec2 a, Vec2 b);

	//������� ������������� ������� ������������� �����
	void d_initMapWay();

	//������������ �� ����-��������� � ���������� ����������
	Vec2 d_convert(Vec2 vec);

	//�������, ������� ���������� ����� �� ����� from �� to
	//��� velocity �����������, � ������� ������ ��������� �����
	//������������ � ��� ��� x � ��� ��� y ��-�����������
	bool d_isBelong(int velocity, float from, float to);

public:
	//���������, ������������ ����������� �� ������� ���� �����������
	const int WALL = -1;
	//���������, ������������ ����������� ������� �� ������� ���� �����������
	const int BLANK = -2;

private:
	TMXTiledMap * _map;

	//������ �� ��������� ����� ������ � ����-�����������
	std::vector<Vec2> _startPoints;

	//������ ������������� ����� � ����-����������� ����
	std::vector< std::vector<int> > _path;

	//*********
	//���������
	//*********

	std::map<std::string, bool> _tasks;
	int _countTasks;

	//��� �����, ������� ������� �������
	Label * _labelTask;

	//������, ������� �������� �������
	std::string _task;

	//��� ����� �� ����, � ������� ����� ������������
	std::string _typeAct;

	//�������, � ������� ����� �������������, ����� ��������� �������
	Vec2 _posTarget;

	//����� ���� � ����
	int _actID;

	//*********
	//��������������� ���
	//P.S. ����� ������ ����� ������
	//*********

	//������ ���� ����������� � ����-�����������
	std::vector<Vec2> _way;

	Sprite * _actor;
	float _speed;

	//������� ��������� ������������ ����� � ����-�����������
	Vec2 _posActorAt;

	//����������, ������� ���������� ��� �� _way � update()
	int _inc;
};
