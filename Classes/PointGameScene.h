#ifndef __PointGame_SCENE_H__
#define __PointGame_SCENE_H__

#include <list>
#include <map>
#include <string>
#include "cocos2d.h"
#include "PointInfo.h"

using namespace std;
USING_NS_CC;

#define HORIZON_SPACE ((Director::getInstance()->getVisibleSize()).width/12)
#define VERTICAL_SPACE ((Director::getInstance()->getVisibleSize()).height/6)
#define MAX_NUM                           5
#define NORMAL_DOT_RADIUS                 10
#define KEY_DOT_RADIUS                    15
#define TOUCH_DIV                         40
#define LEVEL_ROW                         9
#define LEVEL_COLUMN                      9
#define L_R_TAG_SAPCE                     1000
#define MAX_LEVEL_NUM                     12
//
#define RUNNING_SPRITE_TAG                25000
#define LEVEL_PAUSE_LAYER_TAG             25001
#define LEVEL_PASS_LAYER_TAG              25002

#define RETURN_WIDTH                      100
#define RETURN_SCALE_FACTOR               HORIZON_SPACE/2/RETURN_WIDTH

#define START_AGAIN_WIDTH                 100
#define START_AGAIN_SCALE_FACTOR          HORIZON_SPACE/2/START_AGAIN_WIDTH

#define PAUSE_AGAIN_WIDTH                 100
#define PAUSE_AGAIN_SCALE_FACTOR          HORIZON_SPACE/2/PAUSE_AGAIN_WIDTH

#define LEFT_STAR_OFFSET                  100
#define RIGHT_STAR_OFFSET                 100

#define UFO_WIDTH                         100
#define UFO_SCALE_FACTOR                  HORIZON_SPACE/4/UFO_WIDTH

//point name
#define P_NORMAL_IMG_NAME                 "crystal_green.png"
#define P_HIGHLIGHT_IMG_NAME              "crystal_orange.png"
#define P_KEY_IMG_NAME                    "crystal_red.png"

#define POINT_WIDTH                       200
#define POINT_SCALE_FACTOR                HORIZON_SPACE/2/POINT_WIDTH

#define BAFFLE_H_IMG_NAME                 "woodH.png"
#define BAFFLE_V_IMG_NAME                 "woodV.png"
#define BAFFLE_H_WIDTH                    100
#define BAFFLE_SCALE_FACTOR               HORIZON_SPACE/2/BAFFLE_H_WIDTH

class PointInfo;

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

	void onTouchEnded(Touch* touch, Event* event);
	void spriteMoveFinished(Ref* pSender);
    void getVecByTag(int tag, Vec2& point);
	void addRunningSprite(void);
	void getLevelData(void);
	void setCurrentLevel(int level[9][9]);
    void changeImage(int tag, const string& name);
    //level pass
    void leverPass();
    // a selector callback
	void revokeCallback(Ref* pSender);
    void startLevelAgain(Ref* pSender);
    void gamePause(Ref* pSender);
    void gameContinue(Ref* pSender);
    void gameReturnToLevelChoose(Ref* pSender);
    void gameReturnToMainMenu(Ref* pSender);
    void tryAgain(Ref* pSender);
    void nextLevel(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PointGame);
};

#endif // __PointGame_SCENE_H__
