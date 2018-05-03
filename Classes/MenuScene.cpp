#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "AnimationSet.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	return true;
}

void MenuScene::onEnter() {
	Scene::onEnter();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add background
	auto sprite = Sprite::create("textures/background.png");
	sprite->setAnchorPoint(Vec2(0, 0.5));
	sprite->setPosition(Vec2(0, visibleSize.height / 2));
	sprite->setScale(visibleSize.width / sprite->getContentSize().width);
	this->addChild(sprite, 0);

	// add mainMenu
	Menu* mainMenu = Menu::create();
	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

	std::string fontName("fonts/Pixel.ttf");

	// add play button
	Label* play = Label::createWithTTF("Play", fontName, 36);
	MenuItemLabel* playButton = MenuItemLabel::create(play);
	playButton->setPosition(150, 300);
	playButton->setCallback([&](cocos2d::Ref *sender) {
		// replaceScene(BaseGameScene);
	});
	mainMenu->addChild(playButton);

	// add exit button
	Label* exit = Label::createWithTTF("Exit", fontName, 36);
	MenuItemLabel* exitButton = MenuItemLabel::create(exit);
	exitButton->setPosition(150, 200);
	exitButton->setCallback(CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	mainMenu->addChild(exitButton);

	// alising test
	Sprite* test = Sprite::create("textures/large_wood_chest.png");
	test->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	test->setScale(4);

	// gameInfo test
	auto gi = GameInfo::getInstance();
	gi->initWithFile("saves/0");
	LevelInfo* level = gi->getLevel();
	auto actors = level->getActorMap();
	auto role = actors.at("Sven");
	auto behavior = role->getBehavior(-1);
	std::string v_obj = behavior->baseObject->getAttribute("v_obj");

	auto om = ObjectManager::getInstance();
	VisualObject* vobj = om->getVisualObject(v_obj);
	Animation* anim = vobj->getAnimation("run");
	Animate* animate = Animate::create(anim);

	test->runAction(RepeatForever::create(animate));

	this->addChild(test);

	AnimationSet* animSet = AnimationSet::create("animations/large_wood_chest.xml");
	auto anim1 = animSet->getAnimation("open");
	auto anim2 = animSet->getAnimation("close");
	auto act1 = Animate::create(anim1);
	auto act2 = Animate::create(anim2);
	auto seq = Sequence::create(act1, act2, nullptr);
	auto rep = RepeatForever::create(seq);
	auto action = test->runAction(rep);
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
