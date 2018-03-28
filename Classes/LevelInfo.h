#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;

struct Task {
	std::string target; // �����, � �������� ��������� ������
	
};

struct Talk : public Task {
	std::string dialogFile; // ���� ���������� ������ � �������
	int result; // ���������, ������� ���������� ��������

};

struct Defeat : public Task {
	
};

struct Trans�ondition {
	std::vector<Task> tasks; // ������ ������� ������ ��������� �����, ��� �������� � ������ ����
	int next; // id ���������� ���� ��� ��������
	bool final; // ���� ���� ������ �� �����, ������ ��������� � ���������� ����,
	// ����� ��������� �������
};

struct Act {
	std::vector<Trans�ondition> trans; // ������ ���������
};

struct Reward {
	int gold, provision, experience;
	std::vector<std::string> artifacts;
};

struct Role {
	ObjectInfo default; // ��������� �� ���������
	std::map<int, ObjectInfo> changes; // ������ ������������ ���������
};

class LevelInfo {
public:
	LevelInfo(std::string file);
	// �������� ������ �� �����
	bool initWithFile(std::string file);

private:
	// ����, ���������� TMX �����
	std::string _mapFile;
	// ����� � ���� ���������� ������������� ������ �������� � TMX �����
	std::map<std::string, Role> _actors;
	// ����� �������� ��������� ��������� � ���� ����������������� ������ ���������
	std::map<int, Act> _quest;
	// ����� �������� ���������� � ��������� ��������
	std::map<int, Reward> _rewards;

};