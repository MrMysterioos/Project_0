#include "LoadingScene.h"
#include "ObjectManager.h"
#include "ui\CocosGUI.h"
#include "tinyxml2\tinyxml2.h"

USING_NS_CC;
using namespace ui;

// функция асинхронной загрузки ресурсов
bool _loadProcess();
// функция, загружающая спрайт в SpriteFrameCache
bool _loadSprite(std::string id, std::string path);
// функция, загружающая SpriteSheet
bool _loadSpriteSheet(std::string path);
// загрузка анимации
bool _loadAnimation(std::string id, std::string path);
// загрузка шаблонов персонажей
bool _loadCharacters();
// загрузка шаблонов контейнеров
bool _loadContainers();
// загрузка шаблонов костров
bool _loadCampfires();

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

void LoadingScene::update(float dt) {
	if (!_done) {
		if (_loadProcess()) {
			_done = true;
		}
	}
	else {
		_loadCharacters();
		_loadContainers();
		_loadCampfires();
		Director::getInstance()->replaceScene(_replaceScene);
	}
}

LoadingScene::~LoadingScene() {
	_replaceScene->release();
}

bool _loadProcess() {
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
		else if (name == "animation") {
			std::string id = element->Attribute("id");
			std::string path = element->Attribute("path");
			_loadAnimation(id, path);
		}
	}

	element = element->NextSiblingElement();
	return false;

}

bool _loadSprite(std::string id, std::string path) {
	auto cache = SpriteFrameCache::getInstance();
	Sprite* sprite = Sprite::create(path);
	Texture2D* texture = sprite->getTexture();
	Rect rect = sprite->getTextureRect();
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
	cache->addSpriteFrame(frame, id);

	return true;
}

bool _loadSpriteSheet(std::string path) {
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(path);

	return true;
}

bool _loadAnimation(std::string id, std::string path) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile(path.c_str());

	XMLNode* anim = doc.FirstChildElement("Animation");
	if (anim) {
		XMLNode* general = anim->FirstChildElement("general");
		if (general) {
			std::string source = general->Attribute("source");
			int height = atoi(general->Attribute("height"));
			int width = atoi(general->Attribute("width"));
			float duration = atof(general->Attribute("duration"));

			auto animCach = AnimationCache::getInstance();

			Sprite* sprite = Sprite::create(source);
			Texture2D* texture = sprite->getTexture();
			auto textSize = texture->getContentSizeInPixels();

			Vector<SpriteFrame*> animFrames;

			for (int y = 0; y < textSize.height; y += height) {
				for (int x = 0; x < textSize.width; x += width) {
					Rect rect(Vec2(x, y), Size(width, height));
					SpriteFrame* spriteFrame = SpriteFrame::createWithTexture(texture, rect);
					animFrames.pushBack(spriteFrame);
				}
			}

			Animation* anim = Animation::createWithSpriteFrames(animFrames, duration);
			animCach->addAnimation(anim, id);

		}
	}

	return true;

}

bool _loadCharacters() {

	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile("objects/characters.xml");

	XMLNode* characters = doc.FirstChildElement("Characters");
	if (characters) {
		XMLNode* character = characters->FirstChildElement("character");
		while (character) {
			std::string id = character->Attribute("id");
			CharacterTemplate temp;

			XMLNode* properties = character->FirstChildElement("properties");
			if (properties) {
				temp.health = atoi(properties->Attribute("health"));
				temp.speed = atoi(properties->Attribute("speed"));
				temp.damage = atoi(properties->Attribute("damage"));
			}
			
			XMLNode* sprite = character->FirstChildElement("sprite");
			if (sprite) {
				temp.spriteName = sprite->Attribute("name");
			}

			XMLNode* animates = character->FirstChildElement("animations");
			if (animates) {
				XMLNode* anim = animates->FirstChildElement("animation");
				while (anim) {
					std::string name = anim->Attribute("run");
					std::string key = anim->Attribute("while");
					std::pair<std::string, std::string> inf(key, name);
					temp.animationNames.insert(inf);

					anim = anim->NextSiblingElement();
				}
			}

			auto objMan = ObjectManager::getInstance();
			objMan->addCharacterTemplate(id, temp);

			character = character->NextSiblingElement();
		}
	}
	return true;
}

bool _loadContainers() {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile("objects/containers.xml");

	XMLNode* containers = doc.FirstChildElement("Containers");
	if (containers) {
		XMLNode* container = containers->FirstChildElement("container");
		while (container) {
			std::string id = container->Attribute("id");
			ContainerTemplate temp;

			XMLNode* sprite = container->FirstChildElement("sprite");
			if (sprite) {
				temp.spriteName = sprite->Attribute("name");
			}

			XMLNode* animates = container->FirstChildElement("animations");
			if (animates) {
				XMLNode* anim = animates->FirstChildElement("animation");
				while (anim) {
					std::string name = anim->Attribute("run");
					std::string key = anim->Attribute("while");
					std::pair<std::string, std::string> inf(key, name);
					temp.animationNames.insert(inf);

					anim = anim->NextSiblingElement();
				}
			}

			auto objMan = ObjectManager::getInstance();
			objMan->addContainerTemplate(id, temp);

			container = container->NextSiblingElement();
		}
	}
	return true;
}

bool _loadCampfires() {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile("objects/campfires.xml");

	XMLNode* campfires = doc.FirstChildElement("Campfires");
	if (campfires) {
		XMLNode* campfire = campfires->FirstChildElement("campfire");
		while (campfire) {
			std::string id = campfire->Attribute("id");
			CampfireTemplate temp;

			XMLNode* sprite = campfire->FirstChildElement("sprite");
			if (sprite) {
				temp.spriteName = sprite->Attribute("name");
			}

			XMLNode* animates = campfire->FirstChildElement("animations");
			if (animates) {
				XMLNode* anim = animates->FirstChildElement("animation");
				while (anim) {
					std::string name = anim->Attribute("run");
					std::string key = anim->Attribute("while");
					std::pair<std::string, std::string> inf(key, name);
					temp.animationNames.insert(inf);

					anim = anim->NextSiblingElement();
				}
			}

			auto objMan = ObjectManager::getInstance();
			objMan->addCampfireTemplate(id, temp);

			campfire = campfire->NextSiblingElement();
		}
	}
	return true;
}
