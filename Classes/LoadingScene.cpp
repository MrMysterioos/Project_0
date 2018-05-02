#include "LoadingScene.h"
#include "ui\CocosGUI.h"
#include "MenuScene.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;
using namespace ui;

// Функция для загрузки ресурсов
bool _loadRes();

LoadingScene* LoadingScene::createScene() {
	auto scene = LoadingScene::create();
	return scene;
}

bool LoadingScene::init() {

	_loadRes();

	auto dir = Director::getInstance();
	auto size = dir->getVisibleSize();
	auto origin = dir->getVisibleOrigin();

	_loadingBar = LoadingBar::create("ui/loadingBar.png");
	_loadingBar->setAnchorPoint(Vec2(0.5, 0.5));
	_loadingBar->setPosition(Vec2(size.width / 2, size.height / 4));
	_loadingBar->setDirection(LoadingBar::Direction::RIGHT);
	_loadingBar->setPercent(0);

	this->addChild(_loadingBar, 0);

	auto circle = Sprite::create("loading_circle.png");
	circle->setPosition(Vec2(size.width / 2, size.height / 2));

	this->addChild(circle, 0);

	auto turn = RotateBy::create(1, Vec3(0, 0, 180));
	circle->runAction(RepeatForever::create(turn));

	this->scheduleUpdate();

	return true;
}

void LoadingScene::update(float dt) {
	float cur = _loadingBar->getPercent();
	if (cur < 100) {
		_loadingBar->setPercent(cur + dt * 50);
	}
	else {

		Scene* scene = MenuScene::create();
		Director::getInstance()->replaceScene(scene);
	}
}

bool _loadRes() {
	using XMLDoc = tinyxml2::XMLDocument;
	using XMLNode = tinyxml2::XMLElement;

	XMLDoc doc;
	doc.LoadFile("Resources.xml");

	XMLNode* eResources = doc.FirstChildElement("Resources");
	if (eResources) {
		XMLNode* e = eResources->FirstChildElement();
		while (e) {
			std::string name = e->Name();
			if (name == "texture") {
				std::string path = e->Attribute("path");
				Director::getInstance()->getTextureCache()->addImage(path);
			}
			e = e->NextSiblingElement();
		}
	}
	else
		return false;
	return true;
}
