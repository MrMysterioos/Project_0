#pragma once
#include "cocos2d.h"

USING_NS_CC;

/**
 * @brief �����, ������� � ������ ����������� ������������ �������� � ���������� ����� ��������
 *
 * AnimationSet �����, ��� �������� ��������� � ��������� ����������� �������.
 * ������� ������� ������ ���������� ����� �� ���� ���������� ��������� ������� �����.
 * ������ Character, Container, Campfire �������� ���������� ��� AnimationSet.
 */
class AnimationSet : public Ref {
public:
	/**
	 * @brief ������� AnimationSet �� ������ �� �����
	 * @param file ������������� ���� �� ����� � �����������
	 *
	 */
	static AnimationSet* create(std::string file);

	bool init();

	/**
	 * @brief �������������� AnimationSet �� ������ �� �����
	 * @param file ������������� ���� �� ����� � �����������
	 *
	 */
	bool initWithFile(std::string file);

	/**
	 * @brief �����, ������������ ��������� �� Animation �� ��� �����
	 * @param ���� ��� ��������� ��������
	 * @return ��������� �� Animation
	 *
	 * getAnimation - �����, ������������ ��������� �� Animation �� ��� �����.
	 * � ����������� ������� ����� �������� �������� ������ ������ ���������.
	 * ��������, � ������� ������ Character ������ ���� ����� ���� ���: Idle, Walk, Run � ��� �����.
	 */
	inline Animation* getAnimation(std::string key) {
		return _animations.at(key);
	}

	CREATE_FUNC(AnimationSet);
private:
	Map<std::string, Animation*> _animations;
};
