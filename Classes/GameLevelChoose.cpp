#include "GameLevelChoose.h"
#include "Constant.h"
#include "PreLoadScene.h"


using namespace std;

GameLevelChoose::GameLevelChoose(void)
{
	 _level = 1;
}


GameLevelChoose::~GameLevelChoose(void)
{
}

Scene* GameLevelChoose::createScene()
{
	auto scene = Scene::create();
	auto layer = GameLevelChoose::create();
	scene->addChild(layer);
	return scene;
}

bool GameLevelChoose::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//创建关卡选择菜单
	const char* norImg = "choose_level_nor.png";
	const char* lightImg = "choose_level_light.png";
	//创建关卡的循环
	MenuItemImage* levelItem[LEVEL_NUM];
	for(int i=0; i<LEVEL_NUM; i++)
	{
		int index = i + 1;
		levelItem[i] = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(GameLevelChoose::level, this));
		levelItem[i]->setTag(LEVEL_TAG + index);
		
		string txt = to_string(index);
		levelItem[i]->addChild(GameLevelChoose::createLevelTxt(txt));
	}
	//菜单
	auto menu1 = CCMenu::create(levelItem[0], levelItem[1], levelItem[2],  levelItem[3], nullptr);
	auto menu2 = CCMenu::create(levelItem[4], levelItem[5], levelItem[6], levelItem[7], nullptr);
	auto menu3 = CCMenu::create(levelItem[8], levelItem[9], levelItem[10], levelItem[11], nullptr);
	//按照一行4个，4列放置
	menu1->alignItemsHorizontallyWithPadding(20);
	menu2->alignItemsHorizontallyWithPadding(20);
	menu3->alignItemsHorizontallyWithPadding(20);
	menu1->setPosition(Vec2(visibleSize.width/2, visibleSize.height*6.5/8));
	menu2->setPosition(Vec2(visibleSize.width/2, visibleSize.height*4.5/8));
	menu3->setPosition(Vec2(visibleSize.width/2, visibleSize.height*2.5/8));

	addChild(menu1, 1);
	addChild(menu2, 1);
	addChild(menu3, 1);
	return true;
}
Label* GameLevelChoose::createLevelTxt(string& sLvl)
{
	auto level_txt = Label::createWithSystemFont(sLvl, "Arial", 40);
	level_txt->setColor(Color3B::RED);
	level_txt->setPosition(Vec2(40,40));

	return level_txt;
}

void GameLevelChoose::level(Ref* pSender)
{
	MenuItemImage *item = (MenuItemImage *)pSender;
	_level = item->getTag() - LEVEL_TAG;
	CCLOG("level: %d", _level);
	auto scene = PreLoadScene::createScene();
    Constant::level = _level;
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
	
}
