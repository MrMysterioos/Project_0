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

	/**
	* @brief �������� ������ �����
	* @return ���������� ������ ����� � ������
	*/
	inline const Size & getMapSize() { return _map->getMapSize(); }

	/**
	* @brief �������� ������ �����
	* @return ���������� ������ ����� � ��������
	*/
	inline const Size & getTileSize() { return _map->getTileSize() * _map->getScale(); }


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

public:
	//���������, ������������ ����������� �� ������� ���� �����������
	const int WALL = 0;
	//���������, ������������ ����������� ������� �� ������� ���� �����������
	const int BLANK = 1;

private:
	TMXTiledMap * _map;

	//������ �� ��������� ����� ������ � ����-�����������
	std::vector<Vec2> _startPoints;

	//������ ������������� ����� � ����-����������� ����
	std::vector< std::vector<int> > _path;

	PlayerCharacter *_player;

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
};