#include "GameLevelChoose.h"
#include "PointGameScene.h"

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
	//�����ؿ�ѡ��˵�
	const char* norImg = "choose_level_nor.png";
	const char* lightImg = "choose_level_light.png";
	//�����ؿ���ѭ��
	MenuItemImage* levelItem[LEVEL_NUM];
	for(int i=0; i<LEVEL_NUM; i++)
	{
		int index = i + 1;
		levelItem[i] = MenuItemImage::create(norImg, lightImg, CC_CALLBACK_1(GameLevelChoose::level, this));
		levelItem[i]->setTag(LEVEL_TAG + index);
		//itoa(index, txt, 10);
		string txt = to_string(index);
		levelItem[i]->addChild(GameLevelChoose::createLevelTxt(txt));
	}
	//�˵�
	auto menu1 = CCMenu::create(levelItem[0], levelItem[1], levelItem[2],  levelItem[3], nullptr);
	auto menu2 = CCMenu::create(levelItem[4], levelItem[5], levelItem[6], levelItem[7], nullptr);
	auto menu3 = CCMenu::create(levelItem[8], levelItem[9], levelItem[10], levelItem[11], nullptr);
	//����һ��4����4�з���
	menu1->alignItemsHorizontallyWithPadding(20);
	menu2->alignItemsHorizontallyWithPadding(20);
	menu3->alignItemsHorizontallyWithPadding(20);
	menu1->setPosition(ccp(visibleSize.width/2, visibleSize.height*6.5/8));
	menu2->setPosition(ccp(visibleSize.width/2, visibleSize.height*4.5/8));
	menu3->setPosition(ccp(visibleSize.width/2, visibleSize.height*2.5/8));

	addChild(menu1, 1);
	addChild(menu2, 1);
	addChild(menu3, 1);
	return true;
}
Label* GameLevelChoose::createLevelTxt(string& sLvl)
{
	auto level_txt = Label::create(sLvl, "Arial", 40);
	level_txt->setColor(Color3B::RED);
	level_txt->setPosition(ccp(40,40));

	return level_txt;
}

void GameLevelChoose::level(CCObject* pSender)
{
	MenuItemImage *item = (MenuItemImage *)pSender;
	_level = item->getTag()-LEVEL_TAG;
	CCLOG("level: %d", _level);
	auto scene = PointGame::createScene();
	auto layer = (PointGame *)scene->getChildren().at(0);
	layer->curLevelIndex = _level;
	Director::sharedDirector()->replaceScene(TransitionFade::create(1,scene));
	
}