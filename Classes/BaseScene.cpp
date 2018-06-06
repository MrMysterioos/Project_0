#include "BaseScene.h"
#include "GameInfo.h"
#include "DialogScene.h"
#include "DialogSceneEnd.h"
#include "BattleScene.h"
#include "NoPlayerCharacter.h"
#include "cocos2d.h"

using namespace std;

float posCamZ;

Scene* BaseScene::createScene() {
	return BaseScene::create();
}

bool BaseScene::init() {
	//TODO ���������������� �� ����� ����������
	//���� �� ����������� ��� ���� ������ ������, �� ���������� � ����
	_actID = 0;

	_countTasks = 0;

	GameScene::init();

	if (!Scene::init()) {
		return false;
	}

	auto gi = GameInfo::getInstance();
	gi->initWithFile("saves/0");

	//èíèöèàëèçàöèÿ êàðòû
	auto li = gi->getLevel();
	auto quest = li->getQuest();
	auto reward = li->getRewards();
	_map = TMXTiledMap::create(li->getMapSource().c_str());
	_map->setScale(1);
	this->addChild(_map);

	//èíèöèàëèçàöèÿ âåêòîðà ñ íà÷àëüíîé êîîðäèíàòîé
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

	//èíèöèàëèçàöèÿ ïóòè ïåðåìåùåíèÿ
	auto layerPath = _map->getLayer("Path");

	if (layerPath != nullptr) {
		for (int i = 0; i < mapSize.width; i++) {
			_path.push_back(std::vector<int>());
			for (int j = 0; j < mapSize.height; j++) {
				auto spriteTile = layerPath->getTileAt(Vec2(i,mapSize.height - 1 - j));
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

	//èíèöèàëèçàöèÿ ñëóøàòåëÿ
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(BaseScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);


	auto listener = EventListenerCustom::create("BaseScene", [=](EventCustom* event) {
		std::string str("");
		char* buf = static_cast<char*>(event->getUserData());
		str += buf;
		if (getReturnScene(str) == "dialog") {
			int result = getNumberFromExpression(str); 
			_initActByResult(result);
		}
		else if (getReturnScene(str) == "battle") {
			bool result = getNumberFromExpression(str);
			_initActByResult(result);
		}
		int id = _actID;
		auto tta = _typeAct;
		auto x = event->getEventName();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(listener, 1);


	auto actors = li->getActorMap();
	auto playerRole = actors.at("Sven");

	_player = PlayerCharacter::create();
	this->addChild(_player);
	_player->setName("Actor");
	_player->init(playerRole.objInf);
	_player->setPositionInTile(Vec2(6, 4));
	
	// camera
	Node * dummy = Node::create();
	Follow * folDummy = Follow::create(dummy);
	Follow * playerFollow = Follow::create(_player);

	dummy->runAction(playerFollow);
	this->getDefaultCamera()->runAction(folDummy);
	this->addChild(dummy);

	posCamZ = this->getDefaultCamera()->getPositionZ();
	auto x = this->getDefaultCamera()->getPositionZ();
	getDefaultCamera()->setPositionZ( x / 2);

	_updateCamera();

	//èíèöèàëèçàöèÿ ëåéáëà, ïîêàçûâàþùåå òåêóùåå çàäàíèå
	_labelTask = Label::createWithTTF("", "fonts/Pixel.ttf", 15);
	_labelTask->setPosition(this->getDefaultCamera()->getPosition() - Vec2(150, -150));
	_labelTask->setColor(Color3B::RED);
	this->addChild(_labelTask);

	_initActScene(_actID);
	_initNPC();

	this->schedule(schedule_selector(BaseScene::update));
	
	return true;
}

void BaseScene::_initNPC() {

	auto gi = GameInfo::getInstance();
	auto li = gi->getLevel();

	auto actors = li->getActorMap();
	auto playerRole = actors.at("Sven");

	auto Sven = NoPlayerCharacter::create();
	this->addChild(Sven);
	Sven->setName("Sven");
	Sven->init(playerRole.objInf);
	Sven->setBehavior(playerRole.getBehavior(-1));
	Sven->setPositionInTile(Vec2(20, 8));

	auto Copa = NoPlayerCharacter::create();
	this->addChild(Copa);
	Copa->setName("Copa");
	Copa->init(playerRole.objInf);
	Copa->setBehavior(playerRole.getBehavior(-1));
	Copa->setPositionInTile(Vec2(4, 18));

	auto Roka = NoPlayerCharacter::create();
	this->addChild(Roka);
	Roka->setName("Roka");
	Roka->init(playerRole.objInf);
	Roka->setBehavior(playerRole.getBehavior(-1));
	Roka->setPositionInTile(Vec2(6, 18));
}

void BaseScene::_initActScene(int id) {

	auto quest = GameInfo::getInstance()->getLevel()->getQuest();

	//id àêòà íå ìîæåò áûòü áîëüøå êîëè÷åñòâà àêòîâ
	if (id >= quest.size()) {
		return;
	}

	auto transition = quest.find(id)->second.trans.begin();
	auto tasks = transition->tasks;

	_typeAct = transition->tasks.begin()->getTypeName();
	if (_typeAct == "talk") {
		_task = "Talk to ";
	}
	else if (_typeAct == "defeat") {
		_task = "Defeat to ";
	}

	_tasks.clear();

	int count = 1;
	for (auto it = tasks.begin(); it != tasks.end(); ++it) {

		std::string target = it->getAttribute("target");

		if (_typeAct == "defeat") {
			_tasks.insert(std::pair<std::string, bool>(target, false));
			_enemys.push_back(target);
		}

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
	auto objectGroup = _map->getObjectGroup("Actors");
	auto obj = objectGroup->getObject(_targetName);
	auto del = _map->getTileSize();

	_posTarget = Vec2((obj.at("x").asFloat()) / del.width, (obj.at("y").asFloat()) / del.width + 1);
}

void BaseScene::_initActByResult(int result) {
	auto li = GameInfo::getInstance()->getLevel();
	auto quest = li->getQuest();

	//id àêòà íå ìîæåò áûòü áîëüøå êîëè÷åñòâà àêòîâ
	if (_actID >= quest.size()) {
		return;
	}

	auto transition = quest.find(_actID)->second.trans;

	for (auto it : transition) {

		for (auto jt : it.tasks) {
			auto res = jt.getAttribute("result");
			if (result == atoi(res.c_str()) && !it.final) {
				_actID++;
				_initActScene(_actID);
				break;
			}
			else if (result == atoi(res.c_str()) && it.final) {
				//TODO �������� ������� ���������
				auto reward = li->getRewards().at(it.next);
				_posTarget = Vec2(0, 0);
				_task = "You win";
				_labelTask->setString(_task);
			}
		}
	}
}

void BaseScene::_initActByResult(bool result) {
	auto quest = GameInfo::getInstance()->getLevel()->getQuest();

	//id ���� �� ����� ���� ������ ���������� �����
	if (_actID >= quest.size()) {
		return;
	}


	if (result) {
		_initTasksBattleAct();
	}
	else {
		GameOver();
		_posTarget = Vec2(0, 0);
		this->removeChildByName("Actor");
		auto x = _player;
		auto test = 10;
		//this->unschedule(schedule_selector(BaseScene::update));
	}
}

void BaseScene::_initTasksBattleAct() {
	

	if(!_enemys.empty()) {
		_enemys.erase(_enemys.begin());
		this->removeChildByName("Copa");
	}

	if (_enemys.empty()) {
		this->removeChildByName("Roka");
		_posTarget = Vec2(0, 0);
		_actID++;
		_initActScene(_actID);
		return;
	} 

	_posTarget = Vec2(0, 0);

	auto quest = GameInfo::getInstance()->getLevel()->getQuest();

	auto transition = quest.find(_actID)->second.trans.begin();
	auto tasks = transition->tasks;

	auto _targetName = (tasks.begin()+1)->getAttribute("target");
	auto objectGroup = _map->getObjectGroup("Actors");
	auto obj = objectGroup->getObject(_targetName);
	auto del = _map->getTileSize();

	_posTarget = Vec2((obj.at("x").asFloat()) / del.width, (obj.at("y").asFloat()) / del.width + 1);

	/*int count = 0;
	for (auto i : _tasks) {
		if (count == _countTasks) {
			i.second = true;
		}
		count++;
	}

	bool isTrue = true;
	for (auto i : _tasks) {
		if (!i.second) {
			isTrue = false;
			auto x = 5;
		}
	}

	if (isTrue) {
		_countTasks = 0;
		_actID++;
		_initActScene(_actID);
		return;
	}

	_countTasks++;

	auto quest = GameInfo::getInstance()->getLevel()->getQuest();
	auto transition = quest.find(_actID)->second.trans.begin();
	auto tasks = transition->tasks;

	auto _targetName = (tasks.begin() + _countTasks)->getAttribute("target");
	auto objectGroup = _map->getObjectGroup("Actors");
	auto obj = objectGroup->getObject(_targetName);
	auto del = _map->getTileSize();
	_posTarget = Vec2((obj.at("x").asFloat()) / del.width, _map->getMapSize().height - (obj.at("y").asFloat()) / del.width - 2);*/
}

void BaseScene::_updateCamera() {
	auto camera = this->getDefaultCamera();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float Scale = posCamZ / getDefaultCamera()->getPositionZ();

	if (camera->getPosition().x < visibleSize.width / (2.f * Scale)) {
		camera->setPositionX(visibleSize.width / (2.f * Scale));
	}
	else if (camera->getPositionX() > _map->getMapSize().width * _map->getTileSize().width - (visibleSize.width / (2.f * Scale)))
	{
		camera->setPositionX(_map->getMapSize().width * _map->getTileSize().width
			- (visibleSize.width / (2.f * Scale)));
	}

	if (camera->getPositionY() < visibleSize.height / 4.f) {
		camera->setPositionY(visibleSize.height / 4.f);
	}
}

void BaseScene::GameOver() {
	_task = "You died";
	_labelTask->setString(_task);
}

void BaseScene::onMouseDown(Event * event) {
	auto e = (EventMouse*)event;
	float mouseX = e->getCursorX();
	float mouseY = e->getCursorY();

	float Scale = posCamZ / getDefaultCamera()->getPositionZ();

	float x = this->getDefaultCamera()->getPosition().x - Director::getInstance()->getVisibleSize().width / (2.f * Scale);
	float y = (this->getDefaultCamera()->getPosition().y - Director::getInstance()->getVisibleSize().height / (2.f * Scale));

	int tileX = int(((e->getCursorX() + x * Scale) / (_map->getTileSize().width * Scale)));
	int tileY = int((e->getCursorY() + y * Scale) / (_map->getTileSize().height * Scale));

	if (this->getChildByName("Actor")) {
		_player->goTo(Vec2(tileX, tileY));
	}
}

void BaseScene::update(float dt) {
	
	_updateCamera();

	_labelTask->setPosition(this->getDefaultCamera()->getPosition() - Vec2(150, -150));

	if (this->getChildByName("Actor")) {
		if (_player->getPositionInTile() == _posTarget) {
			char buffer[10];
			sprintf_s(buffer, 10, "=%d", _actID);

			_player->stopMoving();

			_posTarget = Vec2(0, 0);

			if (_typeAct == "talk") {

				if (_actID == 0) {

					auto scene = DialogScene::createScene();
					EventCustom event("DialogScene");
					event.setUserData(buffer);
					_eventDispatcher->dispatchEvent(&event);

					Director::getInstance()->pushScene(scene);
				}
				else {

					auto scene = DialogSceneEnd::createScene();
					EventCustom event("DialogSceneEnd");
					event.setUserData(buffer);
					_eventDispatcher->dispatchEvent(&event);

					Director::getInstance()->pushScene(scene);
				}
			}
			else if (_typeAct == "defeat") {
				//TODO call to event BattleScene
				auto scene = BattleScene::createScene();
				EventCustom event("BattleScene");
				event.setUserData(buffer);
				_eventDispatcher->dispatchEvent(&event);

				Director::getInstance()->pushScene(scene);
			}
		}
	}
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
