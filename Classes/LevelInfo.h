#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;

class Task : public Ref {
public:
	std::string target; // �����, � �������� ��������� ������
	
};

class Talk : public Task {
public:
	static Talk* create();

public:
	std::string dialogFile; // ���� ���������� ������ � �������
	int result; // ���������, ������� ���������� ��������

};

class Defeat : public Task {
public:
	static Defeat* create();
};

class Trans�ondition : public Ref {
public:
	static Trans�ondition* create();

public:
	std::vector<Task*> tasks; // ������ ������� ������ ��������� �����, ��� �������� � ������ ����
	int next; // id ���������� ���� ��� ��������
	bool final; // ���� ���� ������ �� �����, ������ ��������� � ���������� ����,
	// ����� ��������� �������
};

class Act : public Ref {
public:
	static Act* create();

public:
	std::vector<Trans�ondition*> trans; // ������ ���������
};

class Reward : public Ref {
public:
	static Reward* create();

public:
	int gold, provision, experience;
	std::vector<std::string> artifacts;
};

class LevelInfo : public Ref {
public:
	LevelInfo* create(std::string file);
	// �������� ������ �� �����
	bool initWithFile(std::string file);

	inline std::string getMapFile() { return _mapFile; }
	inline std::map<std::string, std::map<int, ObjectInfo>> getActorMap() { _actors; }
	inline std::map<int, Act> getQuest() { return _quest; }
	inline std::map<int, Reward> getRewards() { return _rewards; }

private:
	// ����, ���������� TMX �����
	std::string _mapFile;
	// ����� � ���� ���������� ������������� ������ �������� � TMX �����
	std::map<std::string, std::map<int, std::shared_ptr<ObjectInfo>>> _actors;
	// ����� �������� ��������� ��������� � ���� ����������������� ������ ���������
	std::map<int, Act> _quest;
	// ����� �������� ���������� � ��������� ��������
	std::map<int, Reward> _rewards;

};