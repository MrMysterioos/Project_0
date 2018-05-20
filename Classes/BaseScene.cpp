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

	d_initActor();

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
	auto dskl = _posActorAt;
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
	d_update(dt);
}

void BaseScene::onMouseDown(Event * event) {
	d_onMouseDown(event);
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

////ВСПОМОГАТЕЛЬНЫЙ КОД

void BaseScene::d_onMouseDown(Event * event) {
	EventMouse* e = (EventMouse*)event;

	float x = this->getDefaultCamera()->getPosition().x - Director::getInstance()->getVisibleSize().width / 2.f;
	float y = (this->getDefaultCamera()->getPosition().y - Director::getInstance()->getVisibleSize().height / 2.f);

	int tileX = int(((e->getCursorX() + x) / (_map->getTileSize().width * _map->getScale())));
	int tileY = int(_map->getMapSize().height - (e->getCursorY() + y) / (_map->getTileSize().height * _map->getScale()));

	for (int i = tileY; i < _map->getMapSize().height; i++) {
		if (_path[i][tileX] == BLANK) {
			tileY = i;
			break;
		}
	}

	Vec2 toMove = Vec2(tileX, tileY);

	if (d_setWayCoordinate(_posActorAt, toMove))
		this->schedule(schedule_selector(BaseScene::update));
}

void BaseScene::d_update(float dt) {

	if (_posActorAt == _posTarget) {
		_initActByResult(0, 1);
	}

	if (!_way.empty() && _inc < _way.size()) {							//персонажи не должны перемещаться, если нет пути

		if (_posActorAt == _way[_way.size() - 1]) {
			this->unschedule(schedule_selector(BaseScene::update));		//если персонажи прибыли в место назначения - можно больше не двигаться
			return;
		}

		Vec2 velocity = Vec2(_way[_inc].x - _posActorAt.x,
			-(_way[_inc].y - _posActorAt.y));

		if (velocity.x == 0 && velocity.y == 0) {
			_inc++;
			return;
		}

		_actor->setRotationSkewY((1 - velocity.x) * 90);

		_actor->setPosition(Vec2(_actor->getPosition().x + velocity.x * dt * _speed,
			_actor->getPosition().y + velocity.y * dt * _speed));

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto camera = this->getDefaultCamera();


		//X координата смещения камеры
		if (_actor->getPosition().x < visibleSize.width / 2.f) {
			camera->setPositionX(visibleSize.width / 2.f);
		}
		else if (_actor->getPositionX() > _map->getMapSize().width * _map->getTileSize().width * _map->getScale()
			- (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()))
		{
			camera->setPositionX(_map->getMapSize().width * _map->getTileSize().width * _map->getScale()
				- (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()));
		}
		/*else if (_actor->getPositionX() < _map->getMapSize().width * _map->getTileSize().width * _map->getScale()
		- (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()))
		camera->setPositionX(_map->getMapSize().width * _map->getTileSize().width * _map->getScale() - (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()));
		*/
		else {
			camera->setPositionX(_actor->getPositionX());
		}
		_labelTask->setPositionX(camera->getPositionX() - 350);


		//Y координата смещения камеры
		if (_actor->getPositionY() < visibleSize.height / 2.f)
			camera->setPositionY(visibleSize.height / 2.f);
		else if (_actor->getPositionY() > _map->getMapSize().height * _map->getTileSize().height * _map->getScale() - visibleSize.height / 2.f) {
			camera->setPositionY(_map->getMapSize().height * _map->getTileSize().height * _map->getScale() - visibleSize.height / 2.f);
		}
		else {
			camera->setPositionY(_actor->getPositionY());
		}
		_labelTask->setPositionY(camera->getPositionY() + 200);


		/*if (_actor->getPosition().x - this->getDefaultCamera()->getPosition().x > 0) {
		this->getDefaultCamera()->setPosition(velocity.x * _map->getTileSize().width * _map->getScale() * dt + this->getDefaultCamera()->getPosition().x,
		velocity.y * _map->getTileSize().height * _map->getScale() * dt + this->getDefaultCamera()->getPosition().y);
		}*/

		if (d_isBelong(velocity.x, _actor->getPosition().x, d_convert(_way[_inc]).x)
			&& d_isBelong(velocity.y, _actor->getPosition().y, d_convert(_way[_inc]).y))
		{
			_posActorAt = _way[_inc];
			_actor->setPosition(Vec2(d_convert(_posActorAt).x, d_convert(_posActorAt).y));
			_inc++;
		}
	}
}

void BaseScene::d_initActor() {

	//другое
	_speed = 100;

	//инициализация персонажа
	_actor = Sprite::create("textures/warior.png");//Sprite::createWithSpriteFrameName("warior");
	_actor->setPosition(Vec2(d_convert(_startPoints[0])));
	_actor->setScale(2);
	_posActorAt = _startPoints[0];
	this->addChild(_actor);
}

bool BaseScene::d_isBelong(int velocity, float from, float to) {
	if (velocity > 0 && to - from <= 0)
		return true;
	else if (velocity < 0 && to - from >= 0)
		return true;
	else if (velocity == 0)
		return true;
	return false;
}

Vec2 BaseScene::d_convert(Vec2 vec) {
	float x = (vec.x + 0.5f) * _map->getTileSize().width * _map->getScale();
	float y = (_map->getMapSize().height - vec.y) * _map->getTileSize().height * _map->getScale();
	return Vec2(x, y);
}

void BaseScene::d_initMapWay() {
	auto mapSize = _map->getMapSize();
	auto layerPath = _map->getLayer("Path");

	_path.clear();

	if (layerPath != nullptr) {
		for (int i = 0; i < mapSize.height; i++) {
			_path.push_back(std::vector<int>());
			for (int j = 0; j < mapSize.width; j++) {
				auto spriteTile = layerPath->getTileAt(Vec2(j, i));
				if (spriteTile != nullptr) {
					_path[i].push_back(BLANK);
				}
				else
					_path[i].push_back(WALL);
			}
		}
	}
}

bool BaseScene::d_setWayCoordinate(Vec2 a, Vec2 b) {

	auto path = _path;

	auto mapSize = _map->getMapSize();
	_inc = 0;

	_way.clear();
	
	int d, x, y, k;
	bool stop;
	std::vector<Vec2> moveWay;
	int len;

	for (int i = -1; i != 2; i++) {
		for (int j = -1; j != 2; j++) {
			if (i == 0 && j == 0)
				continue;
			moveWay.push_back(Vec2(i, j));
		}
	}  

	if (path[a.y][a.x] == WALL || path[b.y][b.x] == WALL)
		return false;	

	d = 0;
	path[a.y][a.x] = 0;

	do {

		stop = true;

		for (int y = 0; y < path.size(); y++) {
			for (x = 0; x < path[y].size(); x++) {
				if (path[y][x] == d) {
					for (k = 0; k < moveWay.size(); k++) {
						int iy = y + moveWay[k].y, ix = x + moveWay[k].x;
						if (iy >= 0 && iy < mapSize.height && ix >= 0 && ix < mapSize.width &&
							path[iy][ix] == BLANK)
						{
							stop = false;              
							path[iy][ix] = d + 1;
						}
					}
				}
			}
		}
		d++;
	} while (!stop && path[b.y][b.x] == BLANK);

	if (path[b.y][b.x] == BLANK)
		return false;

	len = path[b.y][b.x];
	x = b.x;
	y = b.y;
	d = len;

	_way.resize(d+1);

	while (d > 0) {
		_way[d] = Vec2(x, y);
		d--;
		for (k = 0; k < moveWay.size(); k++) {
			int iy = y + moveWay[k].y, ix = x + moveWay[k].x;
			if (iy >= 0 && iy < mapSize.height && ix >= 0 && ix < mapSize.width &&
				path[iy][ix] == d)
			{
				x = x + moveWay[k].x;
				y = y + moveWay[k].y;          
				break;
			}
		}
	}

	_way[0] = Vec2(a.x, a.y);

	return true;
}


