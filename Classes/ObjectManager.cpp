#include "tinyxml2\tinyxml2.h"
#include "ObjectManager.h"

USING_NS_CC;

static ObjectManager* _objectManager = nullptr;

ObjectManager* ObjectManager::getInstance() {

	if (!_objectManager) {
		_objectManager = new (std::nothrow) ObjectManager();
		_objectManager->init();
	}

	return _objectManager;
}

void ObjectManager::destroyInstance()
{
	CC_SAFE_RELEASE_NULL(_objectManager);
}

bool ObjectManager::init() {



	return true;
}

VisualObject* VisualObject::create(std::string source) {

	VisualObject* ret = new (std::nothrow) VisualObject();
	if (ret->initWithFile(source)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;

}

bool VisualObject::initWithFile(std::string source) {

	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile(source.c_str());
	if (doc.Error())
		return false;

	XMLNode* eObject = doc.FirstChildElement("Object");
	if (eObject) {

		XMLNode* eSprite = eObject->FirstChildElement("sprite");
		if (eSprite) {

			std::string source = eSprite->Attribute("source");
			if (!loadSpriteFrame(source.c_str()))
				return false;

		}

		XMLNode* eAnims = eObject->FirstChildElement("animations");
		if (eAnims) {

			XMLNode* eAnim = eAnims->FirstChildElement("animation");
			while (eAnim) {

				std::string key = eAnim->Attribute("key");
				std::string source = eAnim->Attribute("source");
				if (!loadAnimation(key, source))
					return false;
				eAnim = eAnim->NextSiblingElement();

			}

		}

	}

	return true;

}

void VisualObject::setSpriteFrame(SpriteFrame* frame) {
	_baseSpriteFrame = frame;
	_baseSpriteFrame->retain();
}

void VisualObject::addAnimation(std::string key, Animation* anim) {
	_animations.insert(key, anim);
}

SpriteFrame* VisualObject::getSpriteFrame() {
	return _baseSpriteFrame;
}

/*Animation* VisualObject::getAnimation(std::string key) {
	return _animations.at(key);
}*/

Map<std::string, Animation*> VisualObject::getAnimation() {
	return _animations;
}

bool VisualObject::loadAnimation(std::string key, std::string source) {
	typedef tinyxml2::XMLDocument XMLDoc;
	typedef tinyxml2::XMLElement XMLNode;

	XMLDoc doc;
	doc.LoadFile(source.c_str());

	if (doc.Error())
		return false;

	XMLNode* eAnim = doc.FirstChildElement("Animation");
	if (eAnim) {
		XMLNode* eGeneral = eAnim->FirstChildElement("general");
		if (eGeneral) {
			std::string source = eGeneral->Attribute("source");
			int height = atoi(eGeneral->Attribute("height"));
			int width = atoi(eGeneral->Attribute("width"));
			float duration = atof(eGeneral->Attribute("duration"));

			auto dir = Director::getInstance();
			Texture2D* texture = dir->getTextureCache()->addImage(source);
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
			addAnimation(key, anim);
			return true;
		}
	}

	return false;

}

bool VisualObject::loadSpriteFrame(std::string source) {
	auto dir = Director::getInstance();
	Texture2D* texture = dir->getTextureCache()->addImage(source);
	if (!texture)
		return false;
	Size size = texture->getContentSize();
	Rect rect(Vec2::ZERO, size);
	SpriteFrame* frame = SpriteFrame::createWithTexture(texture, rect);
	setSpriteFrame(frame);

	return true;
}

bool ObjectManager::loadObject(std::string key, std::string source) {

	VisualObject* vobj = VisualObject::create(source);
	if (vobj) {
		_objects.insert(key, vobj);
		return true;
	}
	return false;
	
}

VisualObject* ObjectManager::getVisualObject(std::string key) {
	return _objects.at(key);
}
