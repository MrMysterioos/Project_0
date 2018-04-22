#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"
#include "LevelInfo.h"

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

	private:

		Vector<Behavior*> _heroes;
		std::vector<std::string> _artifacts;
		int _totalTime, _gold, _provision;
		LevelInfo* _level;
		int _curAct;

	private:
		void _destroy();

	};