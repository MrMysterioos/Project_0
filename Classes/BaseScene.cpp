#include "BaseScene.h"
#include "GameInfo.h"
#include "cocos2d.h"
#include "ObjectManager.h"

using namespace std;

Scene* BaseScene::createScene() {
	return BaseScene::create();
}

bool BaseScene::init() {

	GameScene::init();

	if (!Scene::init())
		return false;

	//инициализация карты
	auto gi = GameInfo::getInstance();
	auto li = gi->getLevel();
	_map = TMXTiledMap::create(("maps/" + li->getMapFile()).c_str());
	_map->setScale(2);
	this->addChild(_map);

	//инициализация вектора с начальной координатой
	auto layerStartPoint = _map->getLayer("StartPoints");
	auto mapSize = _map->getMapSize();
	if (layerStartPoint != nullptr) {
		for (int i = 0; i < mapSize.height; i++)
			for (int j = 0; j < mapSize.width; j++) {
				auto spriteTile = layerStartPoint->getTileAt(Vec2(j, i));
				if (spriteTile != nullptr) {
					_startPoints.push_back(Vec2(j, i));
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
				else
					_path[i].push_back(WALL);
			}
		}
	}

	//инициализация персонажа
	_actor = Sprite::createWithSpriteFrameName("warior");
	_actor->setPosition(Vec2(convert(_startPoints[0])));
	_actor->setScale(2);
	_posActorAt = _startPoints[0];
	this->addChild(_actor);

	//log("%f %f", dir->getPosition().x, dir->getPosition().y);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto camera = this->getDefaultCamera();
	camera->setPosition(Vec2(visibleSize.width / 2.f, visibleSize.height / 2.f));

	/*Point origin = Director::getInstance()->getVisibleOrigin();
	Size wsize = Director::getInstance()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
	Point *center = new Point(wsize.width / 2 + origin.x, wsize.height / 2 + origin.y);

	_cameraTarget = Sprite::create();
	_cameraTarget->setPositionX(_actor->getPosition().x); // set to players x
	_cameraTarget->setPositionY(wsize.height / 2 + origin.y); // center of height

	_camera = Follow::create(_cameraTarget, Rect::ZERO);

	this->runAction(_camera);*/

	//log("%f %f", _actor->getPosition().x, _actor->getPosition().y);

	//инициализация слушателя
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(BaseScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//другое
	_speed = 200;

	return true;
}



void BaseScene::update(float dt) {

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

		_actor->setRotationSkewY( (1 - velocity.x) * 90 );

		_actor->setPosition(Vec2( _actor->getPosition().x + velocity.x * dt * _speed , 
			_actor->getPosition().y + velocity.y * dt * _speed ));

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto camera = this->getDefaultCamera();


		//X координата смещения камеры
		if (_actor->getPosition().x < visibleSize.width / 2.f) {
			camera->setPositionX(visibleSize.width / 2.f);
		}
		else if (_actor->getPositionX() > _map->getMapSize().width * _map->getTileSize().width * _map->getScale() 
			- (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()))
			camera->setPositionX(_map->getMapSize().width * _map->getTileSize().width * _map->getScale() - (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()));
		/*else if (_actor->getPositionX() < _map->getMapSize().width * _map->getTileSize().width * _map->getScale()
			- (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()))
			camera->setPositionX(_map->getMapSize().width * _map->getTileSize().width * _map->getScale() - (visibleSize.width / 2.f + 3 * _map->getTileSize().width * _map->getScale()));
			*/
		else
			camera->setPositionX(_actor->getPositionX());


		//Y координата смещения камеры
		if (_actor->getPositionY() < visibleSize.height / 2.f)
			camera->setPositionY(visibleSize.height / 2.f);
		else if(_actor->getPositionY() > _map->getMapSize().height * _map->getTileSize().height * _map->getScale() - visibleSize.height / 2.f) {
			camera->setPositionY(_map->getMapSize().height * _map->getTileSize().height * _map->getScale() - visibleSize.height / 2.f);
		}
		else
			camera->setPositionY(_actor->getPositionY());


		/*if (_actor->getPosition().x - this->getDefaultCamera()->getPosition().x > 0) {
			this->getDefaultCamera()->setPosition(velocity.x * _map->getTileSize().width * _map->getScale() * dt + this->getDefaultCamera()->getPosition().x,
				velocity.y * _map->getTileSize().height * _map->getScale() * dt + this->getDefaultCamera()->getPosition().y);
		}*/

		if( isBelong(velocity.x, _actor->getPosition().x, convert(_way[_inc]).x)
			&& isBelong(velocity.y, _actor->getPosition().y, convert(_way[_inc]).y) ) 
		{
			_posActorAt = _way[_inc];
			_actor->setPosition(Vec2(convert(_posActorAt).x, convert(_posActorAt).y));
			_inc++;
		}
	}
}



void BaseScene::onMouseDown(Event * event) {
	EventMouse* e = (EventMouse*)event;


	log("mouse pos %f %f", e->getCursorX(), e->getCursorY());
	/*log("camera pos %f %f", this->getDefaultCamera()->getPosition().x, this->getDefaultCamera()->getPosition().y);
	log("actor pos %f %f", _actor->getPosition().x, _actor->getPosition().y);
	log("size window %f %f", Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2);*/

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

	/*Vec2 toMove = Vec2( int(((e->getCursorX() + x) / (_map->getTileSize().width * _map->getScale()))), 
		int(_map->getMapSize().height - (e->getCursorY() + y) / (_map->getTileSize().height * _map->getScale())));*/

	Vec2 toMove = Vec2(tileX, tileY);
	
	if(setWayCoordinate(_posActorAt, toMove))
		this->schedule(schedule_selector(BaseScene::update));
}

void BaseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {
	GameScene::onKeyReleased(keyCode, event);
}

void BaseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {

}



bool BaseScene::isBelong(int velocity, float from, float to) {
	if (velocity > 0 && to - from <= 0)
		return true;
	else if (velocity < 0 && to - from >= 0)
		return true;
	else if (velocity == 0)
		return true;
	return false;
}



Vec2 BaseScene::convert(Vec2 vec) {
	float x = (vec.x + 0.5f) * _map->getTileSize().width * _map->getScale();
	float y = (_map->getMapSize().height - vec.y) * _map->getTileSize().height * _map->getScale();
	return Vec2(x, y);
}

void BaseScene::initMapWay() {
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

bool BaseScene::setWayCoordinate(Vec2 a, Vec2 b) {

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

void BaseScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}


