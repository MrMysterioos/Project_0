#pragma once

#include "cocos2d.h"
#include "Behavior.h"
#include "ObjInfo.h"
#include "AnimationSet.h"

class Actor: public Node {
protected:
	Sprite* _sprite;

	ObjectInfo _objInfo;

	AnimationSet *_animationSet;

	short int tileSize = 64;

	virtual bool init();

public:
	/*
	* @brief ������ ����, � ������� ����������� ������
	*
	* @arguments �������� ���������� �����
	*/
	void setPositionInTile(Vec2);
	/*
	* @brief �������� �������� ���������� �������
	*
	* @return �������� ���������� � ���� Vec2
	*/
	Vec2 getPositionInTile();
};