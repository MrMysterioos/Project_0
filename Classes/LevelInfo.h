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

class Role : public Ref {
public:
	static Role* create();

	inline void addBehavior(int key, Behavior* behaviour) { _behaviours.insert(key, behaviour); }
	inline Behavior* getBehavior(int key) { return _behaviours.at(key); }
private:
	Map<int, Behavior*> _behaviours;
};

class LevelInfo : public Ref {
public:
	static LevelInfo* create(std::string file);
	// �������� ������ �� �����
	bool initWithFile(std::string file);

	inline std::string getMapFile() { return _mapFile; }
	inline Map<std::string, Role*> getActorMap() { return _actors; }
	inline Map<int, Act*> getQuest() { return _quest; }
	inline Map<int, Reward*> getRewards() { return _rewards; }

private:
	// ����, ���������� TMX �����
	std::string _mapFile;
	// ����� � ���� ���������� ������������� ������ �������� � TMX �����
	Map<std::string, Role*> _actors;
	// ����� �������� ��������� ��������� � ���� ����������������� ������ ���������
	Map<int, Act*> _quest;
	// ����� �������� ���������� � ��������� ��������
	Map<int, Reward*> _rewards;

};