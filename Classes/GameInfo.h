#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"
#include "LevelInfo.h"

<<<<<<< HEAD
	USING_NS_CC;

	class GameInfo : public Ref {
	public:

		static GameInfo* getInstance();

		static void destroyInstance();

		bool init();
		// функция, которая загружает сохраненные данные из файла.
		// в аргументе указывается дирректория.
		bool initWithFile(std::string source);

		inline Vector<Behavior*> getHeroes() { return _heroes; }
		inline std::vector<std::string> getArtifacts() { return _artifacts; }
		inline int getGolg() { return _gold; }
		inline int getTotalTime() { return _totalTime; }
		inline int getProvision() { return _provision; }
		inline LevelInfo* getLevel() { return _level; }
		inline int getCurAct() { return _curAct; }
=======
USING_NS_CC;
/**
 * @brief Синглтон, содержащий информацию из файла сохранения
 *
 * GameInfo инициализируется при загрудке файла сохранения.
 * Он содержит информацию о героях, их ресурсах, текущем задании и степени прогресса.
 */
class GameInfo : public Ref {
public:

	/**
	 * @brief Метод, возвращающий экземпляр синглтона GameInfo
	 *
	 */
	static GameInfo* getInstance();

	/**
	  * @brief Метод, уничтожающий экземпяр синглтона GameInfo
	  *
	  */
	static void destroyInstance();

	/**
	 * @brief Метод, вызываемый при первом создании объекта
	 *
	 */
	bool init();

	/**
	 * @brief Метод, который загружает сохраненные данные из файла.
	 *
	 * @param [in] source Расположение файла сохранения
	 */
	bool initWithFile(std::string source);

	/**
	 * @brief Метод, возвращающий игровых персонажей
	 * 
	 * getHeroes() возвращает вектор игровых персонажей,
	 * которые были описанны в файле сохранения.
	 * @return Вектор игровых персонажей, входящих в состав команды
	 */
	inline std::vector<ObjectInfo> getHeroes() { return _heroes; }

	/**
	 * @brief Метод, возвращающий набор имеющихся артефактов
	 *
	 */
	inline std::vector<std::string> getArtifacts() { return _artifacts; }

	/**
	 * @brief Получить имеющиеся количество золота
	 *
	 */
	inline int getGolg() { return _gold; }

	/**
	 * @brief Получить глобальное время
	 *
	 */
	inline int getTotalTime() { return _totalTime; }

	/**
	 * @brief Получить общее количество провизии
	 *
	 */
	inline int getProvision() { return _provision; }

	/**
	 * @brief Получить информацию об уровне
	 * @return Экземпляр LevelInfo
	 */
	inline LevelInfo* getLevel() { return _level; }

	/**
	 * @brief Получить id текущего акта
	 *
	 */
	inline int getCurAct() { return _curAct; }
>>>>>>> master

	private:

<<<<<<< HEAD
		Vector<Behavior*> _heroes;
		std::vector<std::string> _artifacts;
		int _totalTime, _gold, _provision;
		LevelInfo* _level;
		int _curAct;

	private:
		void _destroy();

	};
=======
	std::vector<ObjectInfo> _heroes;
	std::vector<std::string> _artifacts;
	int _totalTime, _gold, _provision;
	LevelInfo* _level;
	int _curAct;

private:
	void _destroy();

};
>>>>>>> master
