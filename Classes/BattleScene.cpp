#include "BattleScene.h"

Scene * BattleScene::createScene() {
	return BattleScene::create();
}


bool BattleScene::init() {
	GameScene::init();

	if (!Scene::init()) {
		return false;
	}

	//add background
	auto background = Sprite::create("background_dialog.png");
	background->setPosition(Director::getInstance()->getVisibleSize() / 2);
	this->addChild(background);

	// add mainMenu
	Menu* mainMenu = Menu::create();
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

	std::string fontName("fonts/Pixel.ttf");

	// add war button
	Label* labelWar = Label::createWithTTF("1. War win", fontName, 36);
	MenuItemLabel* warButton = MenuItemLabel::create(labelWar);
	warButton->setPosition(750, 300);
	warButton->setCallback([&](cocos2d::Ref *sender) {
		EventCustom event("BaseScene");

		char buffer[20];
		char nameScene[] = "battle";
		sprintf_s(buffer, 20, "%s=1", nameScene);

		event.setUserData(buffer);
		_eventDispatcher->dispatchEvent(&event);
		Director::getInstance()->popScene();
	});
	mainMenu->addChild(warButton);

	// add peace button
	Label* lavelPeace = Label::createWithTTF("2. You died", fontName, 36);
	MenuItemLabel* peaceButton = MenuItemLabel::create(lavelPeace);
	peaceButton->setPosition(750, 200);
	peaceButton->setCallback([&](cocos2d::Ref *sender) {
		EventCustom event("BaseScene");

		char buffer[20];
		char nameScene[] = "battle";
		sprintf_s(buffer, 20, "%s=0", nameScene);

		event.setUserData(buffer);
		_eventDispatcher->dispatchEvent(&event);
		Director::getInstance()->popScene();
	});
	mainMenu->addChild(peaceButton);

	auto _listener = EventListenerCustom::create("BattleScene", [=](EventCustom* event) {
		std::string str("");
		char* buf = static_cast<char*>(event->getUserData());
		str += buf;
		_actID = getNumberFromExpression(str);
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

	return true;
}

void BattleScene::update(float dt) {

}

void BattleScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}