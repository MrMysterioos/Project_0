#include "DialogScene.h"

Scene* DialogScene::createScene() {
	return DialogScene::create();
}

void DialogScene::setID(int ID) {
}

bool DialogScene::init() {
	GameScene::init();

	if (!Scene::init())
		return false;

	button = Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
	button->setPosition(Vec2(300, 300));

	button->setTitleText("Button Text");

	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED: {
			EventCustom event("game_custom_event1");
			event.setUserData("0 actID");
			_eventDispatcher->dispatchEvent(&event);
			Director::getInstance()->popScene();
			break;
		}
		default:
			break;
		}
	});

	this->addChild(button);

	auto _listener = EventListenerCustom::create("game_custom_event2", [=](EventCustom* event) {
		std::string str("");// ("Custom event 1 received, ");
		char* buf = static_cast<char*>(event->getUserData());
		str += buf;
		_actID = str;
		log("%s", _actID);
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

	return true;
}

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