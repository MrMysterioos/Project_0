#include "GameScene.h"

using namespace cocos2d;

Scene * GameScene::createScene() {
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {

}

void GameScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

int getNumberFromExpression(const std::string & str) {
	std::string strNumber = "";
	bool isDigit = false;
	int number = 0;
	for (unsigned i = 0; i < str.size(); ++i) {
		if (str[i] == '=') {
			isDigit = true;
		}
		if (isDigit && isdigit(str[i])) {
			strNumber += str[i];
		}
	}
	number = atoi(strNumber.c_str());
	return number;
}

const std::string getStringFromInt(int number) {
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

const std::string getReturnScene(const std::string & s) {
	std::string str = "";
	for (unsigned i = 0; i < s.size(); ++i) {
		if (s[i] == '=') {
			break;
		}
		else {
			str += s[i];
		}
	}
	return str;
}