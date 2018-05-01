#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;

/**
 * @brief ������������ ��� ����������� �������, � ������� ����������� ������
 *
 */
enum Team { FRIEND, ENEMY, NEUTRAL };

/**
 * @brief ���������, ������� ������������ ����� ������� ����� ��������� ������
 * 
 * Transition - ���������, ���������� �������� ����� ��������� ������. ������ ��������� �������� ������� ��������,
 * � ���� ������ �����, � ��� �� id ���������� ���� ��� ���������� �������.
 */
struct Transition {
	std::vector<ObjectInfo> tasks; // ������ ������� ������ ��������� �����, ��� �������� � ������ ����
	int next; // id ���������� ���� ��� ��������
	bool final; // ���� ���� ������ �� �����, ������ ��������� � ���������� ����,
	// ����� ��������� �������
};

/**
 * @brief ���������, �������������� �������� ���
 *
 * Act - ���������, ���������� ������� �����. ������ ��������� ��������� ������� �������� � ��������� �����.
 * ����� ����� ������������ ����� ������������ ����, � ���� ������ ���������.
 */
struct Act {
	std::vector<Transition> trans; // ������ ���������
};

/**
 * @brief ��������� - ��������� ����� � ������ (������������ Act), �������� �������� �������
 *
 * Reward - ���������, ���������� �������� �������. ������ ��������� �������� ��������� ����� � ����� ������ (Act ��� ������� ��������).
 */
struct Reward {
	int gold, provision, experience;
	std::vector<std::string> artifacts;
};

/**
* @brief ��������� Behavior �������� �������������� ���������� ��� �������, ������������ �� ���������
*
* Behavior, � ������� �� ObjectInfo, �������� ���������� ���������� �������� �������.
* �������� Behavior ����� ��������� � ��������� ����� �������� ������.
*/
struct Behavior {
	std::string name; // ������������ ���
	Team team; // ������� (����, ���� ��� �����������)
};

/**
 * @brief ���������, ���������������� ��������� ������ (������� �� �����)
 *
 * ��������� Role �������� ����� ���������� �� �������-������, � ����� ��������� � ��� ���������,
 * ��������� �� ����������� ���� ������.
 */
struct Role {
	ObjectInfo objInf;

	inline void addBehavior(int key, Behavior behaviour) { _behaviours.insert(std::pair<int, Behavior>(key, behaviour)); }
	inline Behavior getBehavior(int key) { return _behaviours.at(key); }
private:
	
	std::map<int, Behavior> _behaviours;
};

/**
 * @brief �����, ���������� ��� ���������� �� ������ � ��� ��������
 *
 * ����� LevelInfo �������� � ���� ��������� ���������� �� ������, ����������� �� �����.
 * �� ������ ����� ��������� ������� �����, ��� ����������� ���������� ��������, ��� ���������� �������� ������.
 */
class LevelInfo : public Ref {
public:

	/**
	 * @brief ����� ���������� ������ ��� LevelInfo
	 *
	 * ������ ����������� ����� �� ������ �������� ������ ��� ������ LevelInfo,
	 * �� � �������������� ��� ����� ������ ����� ����������.
	 */
	static LevelInfo* create(std::string file);
	
	/**
	 * @brief �����, ���������������� LevelInfo ����� ������ ����� ����������
	 *
	 */
	bool initWithFile(std::string file);

	/**
	 * @brief �������� ���� �� �����, � ������� �������� �����
	 * @return ���� �� ����� � ���������� � �����
	 */
	inline std::string getMapFile() { return _mapFile; }

	/**
	 * @brief �������� ����� �����
	 * @return ���������� ����� �����
	 */
	inline std::map<std::string, Role> getActorMap() { return _actors; }

	/**
	 * @brief �������� ���� �������
	 * @return ���������� ���� ������ � ���� ������ ����� (������ ���������)
	 */
	inline std::map<int, Act> getQuest() { return _quest; }

	/**
	 * @brief �������� ����� ��������� ��������
	 * @return ���������� ����� ��������� ��������
	 */
	inline std::map<int, Reward> getRewards() { return _rewards; }

private:
	// ����, ���������� TMX �����
	std::string _mapFile;
	// ����� � ���� ���������� ������������� ������ �������� � TMX �����
	std::map<std::string, Role> _actors;
	// ����� �������� ��������� ��������� � ���� ����������������� ������ ���������
	std::map<int, Act> _quest;
	// ����� �������� ���������� � ��������� ��������
	std::map<int, Reward> _rewards;

};