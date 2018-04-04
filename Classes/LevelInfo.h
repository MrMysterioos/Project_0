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

class LevelInfo : public Ref {
public:
	LevelInfo* create(std::string file);
	// загрузка уровня из файла
	bool initWithFile(std::string file);

	inline std::string getMapFile() { return _mapFile; }
	inline std::map<std::string, std::map<int, ObjectInfo>> getActorMap() { _actors; }
	inline std::map<int, Act> getQuest() { return _quest; }
	inline std::map<int, Reward> getRewards() { return _rewards; }

private:
	// файл, содержащий TMX карту
	std::string _mapFile;
	// ключи в этом контейнере соответствуют ключам объектов в TMX карте
	std::map<std::string, std::map<int, std::shared_ptr<ObjectInfo>>> _actors;
	// здесь хранятся квестовые состояния в виде модифицированного списка смежности
	std::map<int, Act> _quest;
	// здесь хранится информация о возможных наградах
	std::map<int, Reward> _rewards;

};