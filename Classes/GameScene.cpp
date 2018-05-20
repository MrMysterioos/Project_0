#include "GameScene.h"

using namespace cocos2d;

Scene * createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::init())
		return false;

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (this->getChildByName("pause") == nullptr) {
			auto layer = PauseMenu::createLayer();
			auto positionCamera = this->getDefaultCamera()->getPosition();
			layer->setName("pause");
			layer->setPosition(positionCamera - Director::getInstance()->getVisibleSize() / 2.f);
			this->addChild(layer);
		}
		else {
			this->removeChildByName("pause");
		}
	}

}

