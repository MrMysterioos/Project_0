#include "PauseMenu.h"

using namespace cocos2d;

Layer * PauseMenu::createLayer() {

	auto layer = PauseMenu::create();	

	return layer;
}

bool PauseMenu::init() {

	if (!Layer::init()){
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add a transparent layer
	auto dn = DrawNode::create();
	dn->drawSolidRect(origin, Vec2(visibleSize.width, visibleSize.height), Color4F(0, 0, 0, 0.5));
	this->addChild(dn, 1);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PauseMenu::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PauseMenu::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Director::getInstance()->getRunningScene()->pause();	

	// add a mainMenu
	Menu* mainMenu = Menu::create();
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

	std::string fontName("fonts/Pixel.ttf");

	// add a resume button
	Label* resume = Label::createWithTTF("Resume", fontName, 36);
	MenuItemLabel* resumeButton = MenuItemLabel::create(resume);
	resumeButton->setPosition(150, 300);
	resumeButton->setCallback([&](cocos2d::Ref *sender) {
		this->removeAllChildren();
		Director::getInstance()->getRunningScene()->resume();
	});
	mainMenu->addChild(resumeButton);

	// add a exit button
	Label* exit = Label::createWithTTF("Exit", fontName, 36);
	MenuItemLabel* exitButton = MenuItemLabel::create(exit);
	exitButton->setPosition(150, 200);
	exitButton->setCallback(CC_CALLBACK_1(PauseMenu::menuCloseCallback, this));
	mainMenu->addChild(exitButton);

	return true;
}

void PauseMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void PauseMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		auto director = Director::getInstance();
		this->removeAllChildren();
		director->getRunningScene()->resume();
	}
}

void PauseMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event) {
	
}