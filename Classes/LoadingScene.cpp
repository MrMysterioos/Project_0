#include "LoadingScene.h"
#include "ui\CocosGUI.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;
using namespace ui;

Scene* LoadingScene::createScene(Scene* replaceScene) {
	auto scene = LoadingScene::create();
	scene->_replaceScene = replaceScene;
	scene->_replaceScene->retain();
	return scene;
}

bool LoadingScene::init() {

	_done = false;

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

bool LoadingScene::_loadRes() {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile("Resources.xml");

	XMLNode* res = doc.FirstChildElement("Resources");
	if (res) {
		XMLNode* texts = res->FirstChildElement("Textures");
		if (texts) {
			XMLNode* text = texts->FirstChildElement();
			while (text) {
				std::string name = text->Name();
				if (name == "sprite") {
					std::string id = text->Attribute("id");
					std::string path = text->Attribute("path");
					_loadSprite(id, path);
				}
				else if (name == "spriteSheet") {
					std::string path = text->Attribute("path");
					_loadSpriteSheet(path);
				}
				text = text->NextSiblingElement();
			}
		}
	}

	return true;
}

bool LoadingScene::_loadProcess() {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	static XMLDoc* doc;
	if (doc == nullptr) {
		doc = new XMLDoc();
		doc->LoadFile("Resources.xml");
	}

	static XMLNode* root, *group, *element;
	if (root == nullptr) {
		root = doc->FirstChildElement();
		if (root) {
			group = root->FirstChildElement();
			if (group) {
				element = group->FirstChildElement();
			}
		}
	}

	if (group == nullptr) {
		root = group = element = nullptr;
		delete doc;
		return true;
	}

	while (element == nullptr) {
		group = group->NextSiblingElement();
		if (group) {
			element = group->FirstChildElement();
		}
		else {
			root = group = element = nullptr;
			delete doc;
			return true;
		}
	}

	std::string groupName = group->Name();
	if (groupName == "Textures") {
		std::string name = element->Name();
		if (name == "sprite") {
			std::string id = element->Attribute("id");
			std::string path = element->Attribute("path");
			_loadSprite(id, path);
		}
		else if (name == "spriteSheet") {
			std::string path = element->Attribute("path");
			_loadSpriteSheet(path);
		}
	}

	element = element->NextSiblingElement();
	return false;

}

bool LoadingScene::_loadSprite(std::string id, std::string path) {
	auto cache = SpriteFrameCache::getInstance();
	Sprite* sprite = Sprite::create(path);
	Texture2D* texture = sprite->getTexture();
	Rect rect = sprite->getTextureRect();
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
	cache->addSpriteFrame(frame, id);

	return true;
}

bool LoadingScene::_loadSpriteSheet(std::string path) {
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(path);

	return true;
}

void LoadingScene::update(float dt) {
	if (!_done) {
		if (_loadProcess()) {
			_done = true;
		}
	}
	else {
		Director::getInstance()->replaceScene(_replaceScene);
	}
}

LoadingScene::~LoadingScene() {
	_replaceScene->release();
}