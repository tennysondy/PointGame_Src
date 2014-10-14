#include "MainScene.h"
#include "GameLevelChoose.h"

USING_NS_CC;

MainScene::MainScene(void)
{
}


MainScene::~MainScene(void)
{
}

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}
bool MainScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto BG = Sprite::create("MainSceneBG.jpg");
	BG->setPosition(visibleSize.width/2, visibleSize.height/2);
	//BG->setOpacity(200);
	this->addChild(BG,0);
	chooseMenu();
	return true;
}
void MainScene::chooseMenu()
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	const char* norImg = "choose_btn_nor.png";
	const char* lightImg = "choose_btn_light.png";

	//biao'ti
    auto title = Label::createWithSystemFont("Start", "Arial", 30);
	title->setPosition(Vec2(60, 35));
    
    
	auto startItem = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(MainScene::startGame, this));
	startItem->addChild(title);

	//”Œœ∑πÊ‘Ú
	title = Label::createWithSystemFont("Role", "Arial", 30);
	title->setPosition(Vec2(60,35));
	auto gameRoleItem = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(MainScene::gameRole, this));
	gameRoleItem->addChild(title);

	//∏¸∂‡”Œœ∑
	title = Label::createWithSystemFont("More", "Arial", 30);
	title->setPosition(Vec2(60,35));
	auto moreGameItem = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(MainScene::moreGame, this));
	moreGameItem->addChild(title);

	//≤Àµ•
	auto menu = CCMenu::create(startItem, gameRoleItem, moreGameItem, nullptr);
	//∑≈‘⁄Õ¨“ª¡–
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));

	this->addChild(menu);
	
}

void MainScene::startGame(Ref* pSender)
{
	CCLOG("startGame");
	auto scene = GameLevelChoose::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
	
}
void MainScene::gameRole(Ref* pSender)
{
	CCLOG("gameRole");
}
void MainScene::moreGame(Ref* pSender)
{
	CCLOG("moreGame");
}