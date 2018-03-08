#include "LoadingScene.h"
#include "ui\CocosGUI.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;
using namespace ui;

Scene* LoadingScene::createScene() {
	return LoadingScene::create();
}

bool LoadingScene::init() {

	auto dir = Director::getInstance();
	auto size = dir->getVisibleSize();
	auto origin = dir->getVisibleOrigin();

	_loadingBar = LoadingBar::create("ui/loadingBar.png");
	_loadingBar->setAnchorPoint(Vec2(0.5, 0.5));
	_loadingBar->setPosition(Vec2(size.width / 2, size.height / 4));
	_loadingBar->setDirection(LoadingBar::Direction::RIGHT);
	_loadingBar->setPercent(0);

	this->addChild(_loadingBar);

	_loadRes();

	Sprite* test1 = Sprite::createWithSpriteFrameName("menuBackgroung");
	this->addChild(test1, 1);

	Sprite* test2 = Sprite::createWithSpriteFrameName("warior_idle1.png");
	test2->setPosition(Vec2(size.width / 2, size.height / 2));
	test2->setScale(5);
	this->addChild(test2, 2);

	Sprite* test3 = Sprite::createWithSpriteFrameName("Warior");
	test3->setPosition(Vec2(size.width / 2 + 300, size.height / 2));
	test3->setScale(5);
	Texture2D::TexParams texParams = { GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
	test3->getTexture()->setTexParameters(texParams);
	this->addChild(test3, 3);

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
				if (name == "spriteSheet") {
					std::string path = text->Attribute("path");
					_loadSpriteSheet(path);
				}
				text = text->NextSiblingElement();
			}
		}
	}

	return true;
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