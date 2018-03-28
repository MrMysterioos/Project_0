#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;

struct Task {
	std::string target; // актер, к которому привязана задача
	
};

struct Talk : public Task {
	std::string dialogFile; // файл содержащий данные о диалоге
	int result; // результат, который необходимо получить

};

struct Defeat : public Task {
	
};

struct TransСondition {
	std::vector<Task> tasks; // задачи которые дллжен выполнить игрок, для перехода к новому акту
	int next; // id сдедующего акта или концовки
	bool final; // если этот флажок не стоит, значит переходим к следующему акту,
	// иначе завершаем задание
};

struct Act {
	std::vector<TransСondition> trans; // список переходов
};

struct Reward {
	int gold, provision, experience;
	std::vector<std::string> artifacts;
};

struct Role {
	ObjectInfo default; // поведение по умолчанию
	std::map<int, ObjectInfo> changes; // замены стандартного поведения
};

class LevelInfo {
public:
	LevelInfo(std::string file);
	// загрузка уровня из файла
	bool initWithFile(std::string file);

private:
	// файл, содержащий TMX карту
	std::string _mapFile;
	// ключи в этом контейнере соответствуют ключам объектов в TMX карте
	std::map<std::string, Role> _actors;
	// здесь хранятся квестовые состояния в виде модифицированного списка смежности
	std::map<int, Act> _quest;
	// здесь хранится информация о возможных наградах
	std::map<int, Reward> _rewards;

};