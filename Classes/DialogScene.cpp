#include "DialogScene.h"

Scene* DialogScene::createScene() {
	return DialogScene::create();
}

bool DialogScene::init() {
	GameScene::init();

	if (!Scene::init()) {
		return false;
	}

	//add background
	auto background = Sprite::create("background_dialog.png");
	background->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(background);


	std::string fontName("fonts/Pixel.ttf");

	mainMenu = Menu::create();
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

	// add war button
	Label* labelWar = Label::createWithTTF("1. Go to the war", fontName, 36);
	MenuItemLabel* warButton = MenuItemLabel::create(labelWar);
	warButton->setPosition(750, 300);
	warButton->setCallback([&](cocos2d::Ref *sender) {
		EventCustom event("BaseScene");

		char buffer[10];
		char nameScene[] = "dialog";
		sprintf_s(buffer, 10, "%s=%d", nameScene, 1);

		event.setUserData(buffer);
		_eventDispatcher->dispatchEvent(&event);
		Director::getInstance()->popScene();
	});
	mainMenu->addChild(warButton);

	// add peace button
	Label* lavelPeace = Label::createWithTTF("2. Don't go to the war", fontName, 36);
	MenuItemLabel* peaceButton = MenuItemLabel::create(lavelPeace);
	peaceButton->setPosition(750, 200);
	peaceButton->setCallback([&](cocos2d::Ref *sender) {
		EventCustom event("BaseScene");

		char buffer[10];
		char nameScene[] = "dialog";
		sprintf_s(buffer, 10, "%s=%d", nameScene, 2);

		event.setUserData(buffer);
		_eventDispatcher->dispatchEvent(&event);
		Director::getInstance()->popScene();
	});
	mainMenu->addChild(peaceButton);

	auto _listener = EventListenerCustom::create("DialogScene", [=](EventCustom* event) {
		std::string str("");
		char* buf = static_cast<char*>(event->getUserData());
		str += buf;
		_actID = getNumberFromExpression(str);
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

	return true;
}

/*
void DialogScene::_init(int id) {

	// add mainMenu

	mainMenu = Menu::create();
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

	if (id == 0) {
	}
	else {
		Label* labelWin = Label::createWithTTF("1. Take the reward", fontName, 36);
		MenuItemLabel* winButton = MenuItemLabel::create(labelWin);
		winButton->setPosition(750, 300);
		winButton->setCallback([&](cocos2d::Ref *sender) {
			EventCustom event("BaseScene");

			char buffer[10];
			char nameScene[] = "dialog";
			sprintf_s(buffer, 10, "%s=%d", nameScene, 1);

			event.setUserData(buffer);
			_eventDispatcher->dispatchEvent(&event);
			Director::getInstance()->popScene();
		});
		mainMenu->addChild(winButton);
	}
}*/

void DialogScene::update(float dt) {

}

void DialogScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {

}

void DialogScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {

}

void DialogScene::onMouseDown(Event * event) {

}

void DialogScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}