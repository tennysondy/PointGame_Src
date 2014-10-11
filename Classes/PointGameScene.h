#ifndef __PointGame_SCENE_H__
#define __PointGame_SCENE_H__

#include <list>
#include <map>
#include "cocos2d.h"
#include "PointInfo.h"
#include "GameLevelChoose.h"

using namespace std;
USING_NS_CC;
#define HORIZON_SPACE ((Director::getInstance()->getVisibleSize()).width/12)
#define VERTICAL_SPACE ((Director::getInstance()->getVisibleSize()).height/6)
#define MAX_NUM 5
#define NORMAL_DOT_RADIUS       10
#define KEY_DOT_RADIUS                15
#define TOUCH_DIV 40
#define LEVEL_ROW              9
#define LEVEL_COLUMN       9
#define L_R_TAG_SAPCE 1000
#define MAX_LEVEL_NUM     12
#define RUNNING_SPRITE_TAG   25000


class PointInfo;
/*
struct PointCmp{
	bool operator () (const PointInfo& point1, const PointInfo& point2){
		
			double e=0.0001;
			if(point1.pos.x>point2.pos.x+e) { return false; }
			if(point1.pos.x<point2.pos.x-e) { return true; }
			if(point1.pos.y>point2.pos.y+e) { return false; }
			if(point1.pos.y<point2.pos.y-e) { return true; }
			
			return false;
		}
	};
*/
class PointGame : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	Vec2 myVecLeft;
	Vec2 myVecRight;
	Vec2 vec_origin;
	Vec2 vec_end;
	void drawInit(int level[2*MAX_NUM-1][2*MAX_NUM-1]);
	bool isTouchPoint(Vec2 vec);
	void drawLine(Vec2 vec1,Vec2 vec2, bool isLeft);
	bool canDrawLine(Vec2 vec1,Vec2 vec2);
	static Rect* createLineRect(Vec2 vec1,Vec2 vec2);
	bool isNeighbor(Vec2 vec1,Vec2 vec2);
	map<int,PointInfo> pointMapLeft;
	map<int,PointInfo> pointMapRight;
	list<PointInfo> pointlist;
	list<Vec2> baffleList;

	list<int> leftPointTagList;
	stack<int> rightPointTagStack;
	stack<int> leftLineTagStack;
	stack<int> rightLineTagStack;
	//int maplength;
	int leftLineTag;
	int rightLineTag;
	int keyPointNum;
	int baffleTag;
	int curLevelIndex;
	int mapLength;
	int curLevel[LEVEL_ROW][LEVEL_COLUMN];
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnter();
    void update(float dt); //定义系统每帧更新函数
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void revokeCallback(Ref* pSender);
	void backToChooseLevel(Ref* pSender);
	void onTouchEnded(Touch* touch, Event* event);
	void spriteMoveFinished(Ref* pSender);
    void getVecByTag(int tag, Vec2& point);
	void addRunningSprite(void);
	void getLevelData(void);
	void setCurrentLevel(int level[9][9]);
    // implement the "static create()" method manually
    CREATE_FUNC(PointGame);
};

#endif // __PointGame_SCENE_H__
