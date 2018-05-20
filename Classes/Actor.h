#include "cocos2d.h"
#include "LevelInfo.h"
#include "AnimationSet.h"

class Actor: public Node {
protected:
	Sprite* _sprite;

	ObjectInfo _objInfo;

	AnimationSet *_animationSet;

	short int tileSize = 64;

	virtual bool init();

public:
	inline void setPositionInTile(Vec2);

	inline Vec2 getPositionInTile();
};