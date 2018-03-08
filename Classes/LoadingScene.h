#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class LoadingScene : public Scene {
public:
	static Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(LoadingScene);

private:
	bool _loadRes();

	bool _loadSprite(std::string id, std::string path);

	bool _loadSpriteSheet(std::string path);

private:
	LoadingBar* _loadingBar;
};