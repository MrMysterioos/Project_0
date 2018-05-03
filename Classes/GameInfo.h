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
		// �������, ������� ��������� ����������� ������ �� �����.
		// � ��������� ����������� �����������.
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
 * @brief ��������, ���������� ���������� �� ����� ����������
 *
 * GameInfo ���������������� ��� �������� ����� ����������.
 * �� �������� ���������� � ������, �� ��������, ������� ������� � ������� ���������.
 */
class GameInfo : public Ref {
public:

	/**
	 * @brief �����, ������������ ��������� ��������� GameInfo
	 *
	 */
	static GameInfo* getInstance();

	/**
	  * @brief �����, ������������ �������� ��������� GameInfo
	  *
	  */
	static void destroyInstance();

	/**
	 * @brief �����, ���������� ��� ������ �������� �������
	 *
	 */
	bool init();

	/**
	 * @brief �����, ������� ��������� ����������� ������ �� �����.
	 *
	 * @param [in] source ������������ ����� ����������
	 */
	bool initWithFile(std::string source);

	/**
	 * @brief �����, ������������ ������� ����������
	 * 
	 * getHeroes() ���������� ������ ������� ����������,
	 * ������� ���� �������� � ����� ����������.
	 * @return ������ ������� ����������, �������� � ������ �������
	 */
	inline std::vector<ObjectInfo> getHeroes() { return _heroes; }

	/**
	 * @brief �����, ������������ ����� ��������� ����������
	 *
	 */
	inline std::vector<std::string> getArtifacts() { return _artifacts; }

	/**
	 * @brief �������� ��������� ���������� ������
	 *
	 */
	inline int getGolg() { return _gold; }

	/**
	 * @brief �������� ���������� �����
	 *
	 */
	inline int getTotalTime() { return _totalTime; }

	/**
	 * @brief �������� ����� ���������� ��������
	 *
	 */
	inline int getProvision() { return _provision; }

	/**
	 * @brief �������� ���������� �� ������
	 * @return ��������� LevelInfo
	 */
	inline LevelInfo* getLevel() { return _level; }

	/**
	 * @brief �������� id �������� ����
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
