#include "DialogSceneEnd.h"

Scene* DialogSceneEnd::createScene() {
	return DialogSceneEnd::create();
}

bool DialogSceneEnd::init() {
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

	auto _listener = EventListenerCustom::create("DialogSceneEnd", [=](EventCustom* event) {
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
}
}*/

void DialogSceneEnd::update(float dt) {

}

void DialogSceneEnd::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {

}

void DialogSceneEnd::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event) {

}

void DialogSceneEnd::onMouseDown(Event * event) {

}

void DialogSceneEnd::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}