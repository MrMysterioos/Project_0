#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;
/**
 * @brief �����, ����������� ����� �����
 *
 * ������ ����� ���������� ����� �������� �����, �� ����� ���� ��� ������������ ���������� �������� ��������.
 */
class LoadingScene : public Scene {
public:

	/**
	 * @brief ����� ��� �������� �����
	 *
	 */
	static LoadingScene* createScene();

	/**
	 * @brief ����� ������������� LoagingScene
	 *
	 */
	virtual bool init() override;

	virtual void update(float dt) override;

	CREATE_FUNC(LoadingScene);

private:
	LoadingBar* _loadingBar;

};