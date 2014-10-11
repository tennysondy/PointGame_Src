#ifndef __MainScene__H__
#define __MainScene__H__
#include "cocos2d.h"
USING_NS_CC;
class MainScene:public Layer
{
public:
	MainScene(void);
	~MainScene(void);
	CREATE_FUNC(MainScene);
	virtual bool init();
	static Scene* createScene();

private:
	//选择菜单
	void chooseMenu();

	//三个菜单的回调函数
	void startGame(Ref* pSender);
	void gameRole(Ref* pSender);
	void moreGame(Ref* pSender);
};

#endif
