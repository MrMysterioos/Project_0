#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

class LoadingScene : public Scene {
public:
	static Scene* createScene(Scene* replaceScene);

	virtual bool init() override;

	virtual void update(float dt) override;

	~LoadingScene();

	CREATE_FUNC(LoadingScene);

private:
	bool _loadProcess();

	bool _loadRes();

	bool _loadSprite(std::string id, std::string path);

	bool _loadSpriteSheet(std::string path);

private:
	LoadingBar* _loadingBar;

	Scene* _replaceScene;

	bool _done;
};