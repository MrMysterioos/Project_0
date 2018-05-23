#include "PlayerCharacter.h"
#include "BaseScene.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter() {};

PlayerCharacter *PlayerCharacter::create(ObjectInfo objInfo) {
	PlayerCharacter *_char = new (std::nothrow) PlayerCharacter();
	if (_char && _char->init(objInfo))
	{
		_char->autorelease();
		return _char;
	}
	CC_SAFE_DELETE(_char);
	return nullptr;
}

bool PlayerCharacter::init(ObjectInfo objInfo) {

	_objInfo = objInfo;

	_healthPoints			= atoi(_objInfo.getAttribute("health").c_str());
	_speed					= atoi(_objInfo.getAttribute("speed").c_str());
	_attackPower			= atoi(_objInfo.getAttribute("damage").c_str());

	std::string resSource	= _objInfo.getAttribute("animation_set");
	_animationSet = AnimationSet::create(resSource);
	_animationSet->retain();

	_sprite = Sprite::create();
	//_sprite->setContentSize(tileSize*2);
	_sprite->setScale(1.5);
	_sprite->setAnchorPoint(Vec2(0.5, 0));
	PlayerCharacter::addChild(_sprite);
	_sprite->retain();

	Animation *_animation = _animationSet->getAnimation("idle");
	Animate *_animate = Animate::create(_animation);
	RepeatForever *_action = RepeatForever::create(_animate);
	_action->setTag(1);
	_sprite->runAction(_action);
	_state = idle;

	_team = FRIEND;
	_name = "Player";

	return true;
}

void PlayerCharacter::update(float dt) {
	static float prevPosition = 0;

	if (prevPosition > getPosition().x)			this->setRotationSkewY(-180);
	else if (prevPosition < getPosition().x)	this->setRotationSkewY(0);

	prevPosition = getPosition().x;

	if (!_way.empty())
	{
		if (_way.front()->isDone())
		{
			_way.front()->release();
			_way.pop();

			if (_way.size() <= 1)
			{
				if (!_way.empty())
					_way.front()->setDuration(1);
				changeState(walk);
			}
			else changeState(run);

			if (!_way.empty())
				this->runAction(_way.front());
		}
		else if (_state == idle)
		{
			_way.front()->setDuration(1);
			this->runAction(_way.front());
			changeState(walk);
		}
	} else {
		changeState(idle);
		unscheduleUpdate();
		/*_animationSet->release();
		_sprite->release();*/
	}
}

void PlayerCharacter::changeState(State newState) {
	if (_state != newState) {
		switch (newState) {
		case idle: {
			_sprite->stopActionByTag(1);
			Animation *_animation = _animationSet->getAnimation("idle");
			Animate *_animate = Animate::create(_animation);
			RepeatForever *_action = RepeatForever::create(_animate);
			_action->setTag(1);
			_sprite->runAction(_action);
			_state = idle;
			break;
		}
		case walk: {
			_sprite->stopActionByTag(1);
			Animation *_animation = _animationSet->getAnimation("walk");
			Animate *_animate = Animate::create(_animation);
			RepeatForever *_action = RepeatForever::create(_animate);
			_action->setTag(1);
			_sprite->runAction(_action);
			_state = walk;
			break;
		}
		case run: {
			_sprite->stopActionByTag(1);
			Animation *_animation = _animationSet->getAnimation("run");
			Animate *_animate = Animate::create(_animation);
			RepeatForever *_action = RepeatForever::create(_animate);
			_action->setTag(1);
			_sprite->runAction(_action);
			_state = run;
			break;
		}
		}
	}
}

void PlayerCharacter::goTo(Vec2 where) {
	auto parent = this->getParent();
	auto scene = dynamic_cast<BaseScene*> (parent);
	Size mapSize = scene->getMapSize();
	std::vector<std::vector<int> > binaryMap = scene->getMapMatrix();

	if (binaryMap[where.x][where.y])
	{
		while (!_way.empty())
			_way.pop();
		unscheduleUpdate();

		std::vector<std::vector<Vec2> > root;
		std::vector<std::vector<int> > distance;
		for (int i = 0; i < mapSize.width; ++i)
		{
			root.push_back(std::vector<Vec2>());
			distance.push_back(std::vector<int>());
			for (int j = 0; j < mapSize.height; ++j)
			{
				root[i].push_back(Vec2(0, 0));
				distance[i].push_back(-1);
			}
		}
		std::queue <Vec2> q;
		q.push(where);
		root[where.x][where.y] = where;
		distance[where.x][where.y] = 0;

		while (!q.empty())
		{
			Vec2 current = q.front();
			q.pop();

			Vec2 Top = current + Vec2(0, 1);
			Vec2 Down = current + Vec2(0, -1);
			Vec2 Right = current + Vec2(1, 0);
			Vec2 Left = current + Vec2(-1, 0);
			Vec2 TopRight = current + Vec2(1, 1);
			Vec2 TopLeft = current + Vec2(1, -1);
			Vec2 DownRight = current + Vec2(-1, 1);
			Vec2 DownLeft = current + Vec2(-1, -1);

			if (Top.y < mapSize.height && binaryMap[Top.x][Top.y])
			{
				binaryMap[Top.x][Top.y] = 0;
				root[Top.x][Top.y] = current;
				distance[Top.x][Top.y] = distance[current.x][current.y] + 1;
				q.push(Top);
			}
			if (Down.y >= 0 && binaryMap[Down.x][Down.y])
			{
				binaryMap[Down.x][Down.y] = 0;
				root[Down.x][Down.y] = current;
				distance[Down.x][Down.y] = distance[current.x][current.y] + 1;
				q.push(Down);
			}
			if (Right.x < mapSize.width && binaryMap[Right.x][Right.y])
			{
				binaryMap[Right.x][Right.y] = 0;
				root[Right.x][Right.y] = current;
				distance[Right.x][Right.y] = distance[current.x][current.y] + 1;
				q.push(Right);
			}
			if (Left.x >= 0 && binaryMap[Left.x][Left.y])
			{
				binaryMap[Left.x][Left.y] = 0;
				root[Left.x][Left.y] = current;
				distance[Left.x][Left.y] = distance[current.x][current.y] + 1;
				q.push(Left);
			}
			if ((TopRight.y < mapSize.height && TopRight.x < mapSize.width) && binaryMap[TopRight.x][TopRight.y])
			{
				binaryMap[TopRight.x][TopRight.y] = 0;
				root[TopRight.x][TopRight.y] = current;
				distance[TopRight.x][TopRight.y] = distance[current.x][current.y] + 1;
				q.push(TopRight);
			}
			if ((TopLeft.y < mapSize.height && TopLeft.x >= 0) && binaryMap[TopLeft.x][TopLeft.y])
			{
				binaryMap[TopLeft.x][TopLeft.y] = 0;
				root[TopLeft.x][TopLeft.y] = current;
				distance[TopLeft.x][TopLeft.y] = distance[current.x][current.y] + 1;
				q.push(TopLeft);
			}
			if ((DownRight.y >= 0 && DownRight.x < mapSize.width) && binaryMap[DownRight.x][DownRight.y])
			{
				binaryMap[DownRight.x][DownRight.y] = 0;
				root[DownRight.x][DownRight.y] = current;
				distance[DownRight.x][DownRight.y] = distance[current.x][current.y] + 1;
				q.push(DownRight);
			}
			if ((DownLeft.y >= 0 && DownLeft.x >= 0) && binaryMap[DownLeft.x][DownLeft.y])
			{
				binaryMap[DownLeft.x][DownLeft.y] = 0;
				root[DownLeft.x][DownLeft.y] = current;
				distance[DownLeft.x][DownLeft.y] = distance[current.x][current.y] + 1;
				q.push(DownLeft);
			}
		}

		Vec2 current = this->getPositionInTile();
		while (current != where)
		{
			Vec2 step = root[current.x][current.y] - current;
			Vec2 stepInPixels = Vec2(step.x * tileSize.width, step.y * tileSize.height);
			MoveBy *move = MoveBy::create(0.3f, stepInPixels);

			move->retain();
			_way.push(move);

			current = root[current.x][current.y];
		}

		scheduleUpdate();
	}
}