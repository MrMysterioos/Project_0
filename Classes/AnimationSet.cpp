#include "AnimationSet.h"
#include "tinyxml2\tinyxml2.h"

AnimationSet* AnimationSet::create(std::string path) {
	auto ret = AnimationSet::create();
	ret->initWithFile(path);
	return ret;
}

bool AnimationSet::init() {

	return true;
}

bool AnimationSet::initWithFile(std::string path) {

	using XMLDoc = tinyxml2::XMLDocument;
	using XMLNode = tinyxml2::XMLElement;

	XMLDoc doc;
	doc.LoadFile(path.c_str());
	if (doc.Error())
		return true;

	XMLNode* eAnims = doc.FirstChildElement("Animations");
	if (eAnims) {
		XMLNode* eAnim = eAnims->FirstChildElement("animation");
		while (eAnim) {
			std::string key = eAnim->Attribute("key");
			std::string source = eAnim->Attribute("source");
			int height = eAnim->IntAttribute("height");
			int width = eAnim->IntAttribute("width");
			float duration = eAnim->FloatAttribute("duration");
			bool reverce = eAnim->BoolAttribute("reverce");

			auto animCach = AnimationCache::getInstance();
			auto textCach = Director::getInstance()->getTextureCache();

			Texture2D* texture = textCach->addImage(source);
			auto textSize = texture->getContentSizeInPixels();

			Vector<SpriteFrame*> animFrames;

			for (int y = 0; y < textSize.height; y += height) {
				for (int x = 0; x < textSize.width; x += width) {
					Rect rect(Vec2(x, y), Size(width, height));
					SpriteFrame* spriteFrame = SpriteFrame::createWithTexture(texture, rect);
					animFrames.pushBack(spriteFrame);
				}
			}

			if (reverce == true) {
				animFrames.reverse();
			}

			Animation* anim = Animation::createWithSpriteFrames(animFrames, duration);
			animCach->addAnimation(anim, path);
			_animations.insert(key, anim);

			eAnim = eAnim->NextSiblingElement();
		}
	}
	else
		return false;

	return true;
}