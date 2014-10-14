#ifndef __GameLevelChoose__H__
#define __GameLevelChoose__H__
#define LEVEL_TAG 100
#define LEVEL_NUM 12
 
#include <string>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class GameLevelChoose:public Layer
{
public:
	GameLevelChoose(void);
	~GameLevelChoose(void);
	virtual bool init();
	CREATE_FUNC(GameLevelChoose);
	static Scene* createScene();
	int _level;
	bool _level_lock;

private:
	//init里面添加菜单，这里是回调函数
	void level(Ref* pSender);

	//根据不同级别createLabel, 菜单标签
	Label* createLevelTxt(string& sLv1);



};

#endif