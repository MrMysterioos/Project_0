#pragma once

#include "cocos2d.h"
#include "ObjInfo.h"

USING_NS_CC;
// класс визуального объекта, €вл€ющийс€
// графическим представлением любого видимого узла на карте
class VisualObject : public Ref {
public:
	static VisualObject* create(std::string source);

	bool initWithFile(std::string source);

	bool loadSpriteFrame(std::string source);
	bool loadAnimation(std::string key, std::string source);

	void setSpriteFrame(SpriteFrame* frame);
	void addAnimation(std::string key, Animation* anim);

	SpriteFrame* getSpriteFrame();
	Animation* getAnimation(std::string key);

	~VisualObject() {
		_baseSpriteFrame->release();
	}

private:
	SpriteFrame* _baseSpriteFrame;
	Map<std::string, Animation*> _animations;

};
// класс, управл€ющий визуальными объектами
class ObjectManager : public Ref {
public:
	
	static ObjectManager* getInstance();

	static void destroyInstance();
	
	bool init();

	bool loadObject(std::string key, std::string source);

	VisualObject* getVisualObject(std::string key);

private:

	Map<std::string, VisualObject*> _objects;

};