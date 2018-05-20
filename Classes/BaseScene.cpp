#include "BaseScene.h"
#include "GameInfo.h"
#include "DialogScene.h"
#include "cocos2d.h"

using namespace std;

Scene* BaseScene::createScene() {
	return BaseScene::create();
}

bool BaseScene::init() {

	//TODO инициализировать из файла сохранения
	//Если он отсутствует или игра только начата, то приравнять к нулю
	_actID = 0;

	GameScene::init();

	if (!Scene::init()) {
		return false;
	}

	auto gi = GameInfo::getInstance();
	gi->initWithFile("saves/0");

	//инициализация карты
	auto li = gi->getLevel();
	auto quest = li->getQuest();
	auto reward = li->getRewards();
	_map = TMXTiledMap::create(li->getMapSource().c_str());
	_map->setScale(2);
	this->addChild(_map);

	//инициализация вектора с начальной координатой
	auto layerStartPoint = _map->getLayer("StartPoints");
	auto mapSize = _map->getMapSize();
	if (layerStartPoint != nullptr) {
		for (unsigned i = 0; i < mapSize.height; ++i) {
			for (unsigned j = 0; j < mapSize.width; ++j) {
				auto spriteTile = layerStartPoint->getTileAt(Vec2(j, i));
				if (spriteTile != nullptr) {
					_startPoints.push_back(Vec2(j, i));
				}
			}
		}
	}

	//инициализация пути перемещения
	auto layerPath = _map->getLayer("Path");

	if (layerPath != nullptr) {
		for (int i = 0; i < mapSize.height; i++) {
			_path.push_back(std::vector<int>());
			for (int j = 0; j < mapSize.width; j++) {
				auto spriteTile = layerPath->getTileAt(Vec2(j, i));
				if (spriteTile != nullptr) {
					_path[i].push_back(BLANK);
				}
				else {
					_path[i].push_back(WALL);
				}
			}
		}
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto camera = this->getDefaultCamera();
	camera->setPosition(Vec2(visibleSize.width / 2.f, visibleSize.height / 2.f));

	//инициализация слушателя
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(BaseScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//инициализация лейбла, показывающее текущее задание
	_labelTask = Label::createWithTTF("", "fonts/Pixel.ttf", 35);
	_labelTask->setPosition(camera->getPosition() - Vec2(350, -200));
	_labelTask->setColor(Color3B::RED);
	_labelTask->setOpacity(0);
	this->addChild(_labelTask);

	_initActScene(_actID);

	//НАРАБОТКИ
	auto listener = EventListenerCustom::create("game_custom_event1", [=](EventCustom* event) {
		/*std::string str("Custom event 1 received, ");
		char* buf = static_cast<char*>(event->getUserData());
		str += buf;
		str += " times";
		auto x = event->getEventName();*/
	});
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

	return true;
}

void BaseScene::_initActScene(int id) {

	auto quest = GameInfo::getInstance()->getLevel()->getQuest();

	//id акта не может быть больше количества актов
	if (id >= quest.size()) {
		return;
	}

	auto transition = quest.find(id)->second.trans.begin();
	auto tasks = transition->tasks;

	std::string typeAct = transition->tasks.begin()->getTypeName();
	if (typeAct == "talk") {
		_task = "Talk to ";
	}
	else if (typeAct == "defeat") {
		_task = "Defeat to ";
	}

	int count = 1;
	for (auto it = tasks.begin(); it != tasks.end(); ++it) {

		std::string target = it->getAttribute("target");

		//TODO поработать над алгоритмами, чтобы выводило задание красиво
		if (_task.size() > unsigned(10 * count)) {
			_task += "\n";
			count++;
		}

		if (it == tasks.begin()) {
			_task += target;
			continue;
		}
		else if (it != tasks.end() - 1) {
			std::string str = ", " + target;
			_task += str;
		}
		else {
			std::string str = " and " + target;
			_task += str;
		}
	}
	_labelTask->setString(_task.c_str());

	auto _targetName = tasks.begin()->getAttribute("target");
	auto objectGroup =_map->getObjectGroup("Actors");
	auto obj = objectGroup->getObject(_targetName);

	auto del = _map->getTileSize();

	_posTarget = Vec2((obj.at("x").asFloat()) / del.width, _map->getMapSize().height - (obj.at("y").asFloat()) / del.width-2);
}

void BaseScene::_initActByResult(int id, int result) {
	auto quest = GameInfo::getInstance()->getLevel()->getQuest();

	//id акта не может быть больше количества актов
	if (id >= quest.size()) {
		return;
		}

	auto transition = quest.find(id)->second.trans;
	//auto tasks = transition->tasks;

	for (auto it : transition) {

		for (auto jt : it.tasks) {
			auto res = jt.getAttribute("result");
			if (result == atoi(res.c_str()) && !it.final) {
				_actID++;
				_initActScene(_actID);
				break;
			}
			else if (result == atoi(res.c_str()) && it.final) {
				//TODO получение награды
			}
		}
	}
}

void BaseScene::_initActByResult(int id, bool result) {

}

void BaseScene::update(float dt) {
}

void BaseScene::onMouseDown(Event * event) {
}

void BaseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {
	GameScene::onKeyReleased(keyCode, event);
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB) {
		_labelTask->setOpacity(0);
	}
}

void BaseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_TAB) {
		_labelTask->setOpacity(1000);
	}
}


