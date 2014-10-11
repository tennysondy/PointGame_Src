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
	//ѡ��˵�
	void chooseMenu();

	//�����˵��Ļص�����
	void startGame(Ref* pSender);
	void gameRole(Ref* pSender);
	void moreGame(Ref* pSender);
};

#endif
