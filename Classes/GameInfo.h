#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"
#include "LevelInfo.h"

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
	inline int getGold() { return _gold; }

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

private:

	std::vector<ObjectInfo> _heroes;
	std::vector<std::string> _artifacts;
	int _totalTime, _gold, _provision;
	LevelInfo* _level;
	int _curAct;

private:
	void _destroy();

};