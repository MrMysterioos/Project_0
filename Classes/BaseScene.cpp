#include "BaseScene.h"
#include "GameInfo.h"
#include "cocos2d.h"

using namespace std;

Scene* BaseScene::createScene() {
	return BaseScene::create();
}

bool BaseScene::init() {

	_speed = 50;
	

	GameScene::init();

	if (!Scene::init())
		return false;


	auto gi = GameInfo::getInstance();
	auto li = gi->getLevel();

	log("%s", li->getMapFile().c_str());

	_map = TMXTiledMap::create("maps/test_map2.tmx");
	this->addChild(_map);
	
	//log("startPoints:");

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

	/*for (int i = 0; i < _startPoints.size(); i++)
		log("%f %f", _startPoints[i].x, _startPoints[i].y);

	log("Path:");*/


	//инициализация вектора пути перемещения	

	
	/*for (int i = 0; i < _path.size(); i++)
		for (int j = 0; j < _path[i].size(); j++) {
			if (_path[i][j] == BLANK) {
				log("%d %d",j, i);
			}
		}*/

	_actor = Sprite::create("textures/Warior.png");
	_actor->setPosition(Vec2(convertToCoordinate(_startPoints[1])));
	_posActorAt = _startPoints[0];
	this->addChild(_actor);

	//log("WWW: %f %f", _posActorAt.x, _posActorAt.y);
	//log("Path: %d", _path[_posActorAt.y][_posActorAt.x]);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(BaseScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	/*camera = Follow::create(_actor, Rect::ZERO);
	this->runAction(camera);*/

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

void BaseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {
	GameScene::onKeyReleased(keyCode, event);
}

void BaseScene::onMouseDown(Event * event) {
	/*EventMouse* e = (EventMouse*)event;
	Vec2 toMove = Vec2(int(e->getCursorX()/32), int(_map->getMapSize().height - e->getCursorY()/32));
	if(setWayCoordinate(_posActorAt, toMove))
		this->schedule(schedule_selector(BaseScene::update));

	log("yes");*/
}

void BaseScene::update(float dt) {
	/*if (!_way.empty() && _inc < _way.size()) {
		if (_posActorAt == _way[_way.size()-1])
			this->unschedule(schedule_selector(BaseScene::update));
		Vec2 velocity = Vec2(_way[_inc].x - _posActorAt.x, -(_way[_inc].y - _posActorAt.y));
		if (velocity.x == 0 && velocity.y == 0) {
			_inc++;
			return;
		}
		//if (_posActorAt.y == _way[_inc].y) {
		_actor->setPosition(Vec2(_actor->getPosition().x + velocity.x * dt * _speed, _actor->getPosition().y + velocity.y * dt * _speed));
		//}
		if (int(_way[_inc].x * 32 - _actor->getPosition().x) == 0 && int(convertToCoordinate(_way[_inc]).y - _actor->getPosition().y) == 0) {
			//_inc++;
			_posActorAt = _way[_inc];
		}
		log("inc %d", _inc);
	}*/
}

void BaseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {

}

bool BaseScene::setWayCoordinate(Vec2 a, Vec2 b) {

	auto mapSize = _map->getMapSize();
	auto layerPath = _map->getLayer("Path");
	_inc = 0;

	_way.clear();
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

	if (_path[a.y][a.x] == WALL || _path[b.y][b.x] == WALL)
		return false;

	

	d = 0;
	_path[a.y][a.x] = 0;

	do {

		stop = true;

		for (int y = 0; y < _path.size(); y++) {
			for (x = 0; x < _path[y].size(); x++) {
				if (_path[y][x] == d) {
					for (k = 0; k < moveWay.size(); k++) {
						int iy = y + moveWay[k].y, ix = x + moveWay[k].x;
						if (iy >= 0 && iy < mapSize.height && ix >= 0 && ix < mapSize.width &&
							_path[iy][ix] == BLANK)
						{
							stop = false;              
							_path[iy][ix] = d + 1;
						}
					}
				}
			}
		}
		d++;
	} while (!stop && _path[b.y][b.x] == BLANK);

	if (_path[b.y][b.x] == BLANK)
		return false;

	len = _path[b.y][b.x];
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
				_path[iy][ix] == d)
			{
				x = x + moveWay[k].x;
				y = y + moveWay[k].y;          
				break;
			}
		}
	}

	_way[0] = Vec2(a.x, a.y);

	for (int i = 0; i < _way.size(); i++) {
		log("%f %f", _way[i].x, _way[i].y);
	}

	return true;
}

Vec2 BaseScene::convertToCoordinate(Vec2 vec) {
	float x = vec.x * 32;
	float y = (_map->getMapSize().height - vec.y) * 32;
	return Vec2(x, y);
}


