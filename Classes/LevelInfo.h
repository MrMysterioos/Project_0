#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;

class Task : public Ref {
public:
	std::string target; // актер, к которому привязана задача
	
};

class Talk : public Task {
public:
	static Talk* create();

public:
	std::string dialogFile; // файл содержащий данные о диалоге
	int result; // результат, который необходимо получить

};

class Defeat : public Task {
public:
	static Defeat* create();
};

class TransСondition : public Ref {
public:
	static TransСondition* create();

public:
	std::vector<Task*> tasks; // задачи которые дллжен выполнить игрок, для перехода к новому акту
	int next; // id сдедующего акта или концовки
	bool final; // если этот флажок не стоит, значит переходим к следующему акту,
	// иначе завершаем задание
};

class Act : public Ref {
public:
	static Act* create();

public:
	std::vector<TransСondition*> trans; // список переходов
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
	// загрузка уровня из файла
	bool initWithFile(std::string file);

	inline std::string getMapFile() { return _mapFile; }
	inline Map<std::string, Role*> getActorMap() { return _actors; }
	inline Map<int, Act*> getQuest() { return _quest; }
	inline Map<int, Reward*> getRewards() { return _rewards; }

private:
	// файл, содержащий TMX карту
	std::string _mapFile;
	// ключи в этом контейнере соответствуют ключам объектов в TMX карте
	Map<std::string, Role*> _actors;
	// здесь хранятся квестовые состояния в виде модифицированного списка смежности
	Map<int, Act*> _quest;
	// здесь хранится информация о возможных наградах
	Map<int, Reward*> _rewards;

};