#include "cocos2d.h"
#include "Behavior.h"
#include "ObjInfo.h"
#include "AnimationSet.h"
#include "BaseScene.h"

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