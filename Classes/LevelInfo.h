#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"
#include "Behavior.h"

USING_NS_CC;

/**
 * @brief Структура, которая представляет собой переход между сюжетными актами
 * 
 * Transition - структура, являющаяся переходм между сюжетными актами. Данная структура содержит условия перехода,
 * в виде набора задач, а так же id следующего акта или завершения задания.
 */
struct Transition {
	std::vector<ObjectInfo> tasks; // задачи которые дллжен выполнить игрок, для перехода к новому акту
	int next; // id сдедующего акта или концовки
	bool final; // если этот флажок не стоит, значит переходим к следующему акту,
	// иначе завершаем задание
};

/**
 * @brief Структура, представляющая сюжетный акт
 *
 * Act - структура, являющаяся сюжетым актом. Данная структура описывает условия перехода к следующим актам.
 * Набор актов представляет собой направленный граф, в виде списка смежности.
 */
struct Act {
	std::vector<Transition> trans; // список переходов
};

/**
 * @brief Структура - финальная точка в сюжете (альтернатива Act), содержит призовые ресурсы
 *
 * Reward - структура, содержащая призовые ресурсы. Данная структура является тупиковым узлом в графе сюжета (Act без условий перехода).
 */
struct Reward {
	int gold, provision, experience;
	std::vector<std::string> artifacts;
};

/**
 * @brief Структура, предопределяющая поведение актера (объекта на сцене)
 *
 * Структура Role содержит общую информацию об объекте-актере, а также изменения в его поведении,
 * зависящие от конкретного акта сюжета.
 */
struct Role {
	ObjectInfo objInf;

	inline void addBehavior(int key, Behavior behaviour) { _behaviours.insert(std::pair<int, Behavior>(key, behaviour)); }
	inline Behavior getBehavior(int key) { return _behaviours.at(key); }
private:
	
	std::map<int, Behavior> _behaviours;
};

/**
 * @brief Класс, содержащий всю информацию об уровне и его сценарии
 *
 * Класс LevelInfo содержит в себе статичную информацию об уровне, загруженную из файла.
 * На данный класс опираются игровые сцены, для определения дальнейших действий, при следовании сценарию уровня.
 */
class LevelInfo : public Ref {
public:

	/**
	 * @brief Метод выделяжший память под LevelInfo
	 *
	 * Данный статический метод не только выделяет память под объект LevelInfo,
	 * но и инициализирует его путем чтения файла параметров.
	 */
	static LevelInfo* create(std::string file);
	
	/**
	 * @brief Метод, инициализирующий LevelInfo путем чтения файла параметров
	 *
	 */
	bool initWithFile(std::string file);

	/**
	 * @brief Получить путь до файла, в котором хранится карта
	 * @return Путь до файла с информацей о карте
	 */
	inline std::string getMapSource() { return _source + "/map.tmx"; }

	/**
	 * @brief Получить карту ролей
	 * @return Карту ролей
	 */
	inline std::map<std::string, Role> getActorMap() { return _actors; }

	/**
	 * @brief Получить граф задания
	 * @return Возвращает граф сюжета в виде набора актов (списка смежности)
	 */
	inline std::map<int, Act> getQuest() { return _quest; }

	/**
	 * @brief Получить набор различных концовок
	 * @return Набор различных концовок
	 */
	inline std::map<int, Reward> getRewards() { return _rewards; }

private:
	// путь до источника
	std::string _source;
	// ключи в этом контейнере соответствуют ключам объектов в TMX карте
	std::map<std::string, Role> _actors;
	// здесь хранятся квестовые состояния в виде модифицированного списка смежности
	std::map<int, Act> _quest;
	// здесь хранится информация о возможных наградах
	std::map<int, Reward> _rewards;

};