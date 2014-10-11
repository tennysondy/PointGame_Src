#include "MainScene.h"
#include "GameLevelChoose.h"



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

	//开始
	auto title = Label::create("Start", "Arial",30);
	title->setPosition(ccp(60,35));
	auto startItem = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(MainScene::startGame, this));
	startItem->addChild(title);

	//游戏规则
	title = Label::create("Role", "Arial", 30);
	title->setPosition(ccp(60,35));
	auto gameRoleItem = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(MainScene::gameRole, this));
	gameRoleItem->addChild(title);

	//更多游戏
	title = Label::create("More", "Arial", 30);
	title->setPosition(ccp(60,35));
	auto moreGameItem = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(MainScene::moreGame, this));
	moreGameItem->addChild(title);

	//菜单
	auto menu = CCMenu::create(startItem, gameRoleItem, moreGameItem, nullptr);
	//放在同一列
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));

	this->addChild(menu);
	
}

void MainScene::startGame(Ref* pSender)
{
	CCLog("startGame");
	auto scene = GameLevelChoose::createScene();
	//auto layer = Layer::create();
	//scene->addChild(layer);
	Director::sharedDirector()->replaceScene(TransitionFade::create(1,scene));
	
}
void MainScene::gameRole(Ref* pSender)
{
	CCLog("gameRole");
}
void MainScene::moreGame(Ref* pSender)
{
	CCLog("moreGame");
}