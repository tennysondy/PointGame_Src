#include <stack>
#include <list>
#include <map>
#include <iostream>
#include <math.h>
#include "PointGameScene.h"
#include "PointInfo.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Level.h"
#include "Constant.h"
#include "PreLoadScene.h"
#include "GameLevelChoose.h"
#include "MainScene.h"
#include "DrawLightning.h"

USING_NS_CC;

using namespace std;
using namespace CocosDenshion;

#pragma mark - cocos2dx init functions

Scene* PointGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	//auto layer = LayerColor::create(Color4B(255,255,0,111));
	auto layer = PointGame::create();
	
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool PointGame::init()
{
	this->leftLineTag=10000;
	this->rightLineTag=11000;
	this->baffleTag=5000;
	this->keyPointNum=0;
	this->mapLength=100;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto layer = LayerColor::create(Color4B(255, 255, 255, 255));
	//this->addChild(layer, 0);
    
    //background
    auto bg = Sprite::create("bg4S.png", Rect(0, 0, 960, 640));
    bg->setAnchorPoint(Vec2(0, 0));
    this->addChild(bg, 0);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto pauseItem = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(PointGame::gamePause, this));
    pauseItem->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y + visibleSize.height - 15));
    //pauseItem->setScale(PAUSE_AGAIN_SCALE_FACTOR);
    pauseItem->setAnchorPoint(Vec2(1, 1));
    auto menuPauseItem = Menu::create(pauseItem, nullptr);
    menuPauseItem->setPosition(Vec2::ZERO);
    this->addChild(menuPauseItem, 1);
    
    float x = pauseItem->getPosition().x - pauseItem->getContentSize().width;
    float y = pauseItem->getPosition().y;
    
    auto startAgainItem = MenuItemImage::create("startAgain.png", "startAgain.png", CC_CALLBACK_1(PointGame::startLevelAgain, this));
    startAgainItem->setPosition(Vec2(x - 15, origin.y + y));
    //startAgain->setScale(START_AGAIN_SCALE_FACTOR);
    startAgainItem->setAnchorPoint(Vec2(1, 1));
    auto menuStartAgain = Menu::create(startAgainItem, nullptr);
    menuStartAgain->setPosition(Vec2::ZERO);
    this->addChild(menuStartAgain, 1);
    
    auto revokeItem = MenuItemImage::create(
                                            "eraser50.png",
                                            "eraser50.png",
                                            CC_CALLBACK_1(PointGame::revokeCallback,this));
    x = startAgainItem->getPosition().x - startAgainItem->getContentSize().width;
	revokeItem->setPosition(Vec2(x - 50, origin.y + y));
    revokeItem->setAnchorPoint(Vec2(1, 1));
	auto menuRevokeItem = Menu::create(revokeItem, nullptr);
	menuRevokeItem->setPosition(Vec2::ZERO);
	this->addChild(menuRevokeItem, 1);
    
    this->scheduleUpdate();

    return true;
}

void PointGame::onEnter()
{
	Layer::onEnter();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->curLevelIndex = Constant::level;
	CCLOG("index: %d", this->curLevelIndex);
    
    //添加标题
    string a = "LEVEL  ";
    string index = to_string(this->curLevelIndex);
    string text = a+index;
    auto title = LabelTTF::create(text, "Marker Felt.ttf", 44);
	title->setColor(Color3B::BLACK);
    // position the label on the center of the screen
    title->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - title->getContentSize().height));
    
    // add the label as a child to this layer
	this->addChild(title, 1);
    
	getLevelData();
	PointGame::drawInit(this->curLevel);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		return true;
	};
	listener->onTouchEnded = CC_CALLBACK_2(PointGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

#pragma mark - Level data

void PointGame::setCurrentLevel(int level[LEVEL_ROW][LEVEL_COLUMN])
{
	for (int i = 0; i < LEVEL_ROW; i++)
	{
		for (int j = 0; j < LEVEL_COLUMN; j++)
		{
			this->curLevel[i][j] = level[i][j];
		}
	}
}

void PointGame::getLevelData(void)
{
	switch (this->curLevelIndex)
	{
	case 1:
		setCurrentLevel(level1);
		break;
	case 2:
		setCurrentLevel(level2);
		break;
	case 3:
		setCurrentLevel(level3);
		break;
	case 4:
		setCurrentLevel(level4);
		break;
	case 5:
		setCurrentLevel(level5);
		break;
	case 6:
		setCurrentLevel(level6);
		break;
	case 7:
		setCurrentLevel(level7);
		break;
	case 8:
		setCurrentLevel(level8);
		break;
	case 9:
		setCurrentLevel(level9);
		break;
	case 10:
		setCurrentLevel(level10);
		break;
	case 11:
		setCurrentLevel(level11);
		break;
	case 12:
		setCurrentLevel(level12);
		break;
	default:
		break;
	}
}

#pragma mark - Draw points and lines

void PointGame::drawInit(int level[2*MAX_NUM-1][2*MAX_NUM-1])
{
	for(int i = 0; i < 6; i++)
	{
		if(i == MAX_NUM)
		{
			Vec2 start = Vec2((i+1)*HORIZON_SPACE, VERTICAL_SPACE);
			Vec2 end = Vec2((i+1)*HORIZON_SPACE, MAX_NUM*VERTICAL_SPACE);
			auto line = DrawNode::create();
			addChild(line, 1);
			line->drawSegment(start, end, 2, Color4F(1,0,0.2,1));
		}
		else if(i < MAX_NUM)
		{
			PointInfo myPointLeft;
			for(int j = 0; j < MAX_NUM; j++)
			{
				myVecLeft = Vec2((i+1)*HORIZON_SPACE, (j+1)*VERTICAL_SPACE);
				auto r= DrawNode::create();
				r->setAnchorPoint(Vec2(0.5,0.5));
				addChild(r, 2);  
				r->setTag(this->mapLength);
				//r->drawDot(myVecLeft, NORMAL_DOT_RADIUS, Color4F(0,0,0,1));
                
				myPointLeft.tag = r->getTag();
				myPointLeft.pos = myVecLeft;
                myPointLeft.flag = false;

				this->pointMapLeft.insert(pair<int,PointInfo>(this->mapLength,myPointLeft));
                
                
                //create star sprite
                auto texture = Director::getInstance()->getTextureCache()->addImage(P_NORMAL_IMG_NAME);
                auto star = Sprite::createWithTexture(texture);
                star->setScale(POINT_SCALE_FACTOR);
                star->setTag(this->mapLength+LEFT_STAR_OFFSET);
                star->setPosition(myVecLeft);
                star->setAnchorPoint(Vec2(0.5, 0.5));
                this->addChild(star, 3);
                
                
				this->mapLength++; 
		        //CCLog("point x: %f, y: %f", myPointLeft.pos.x, myPointLeft.pos.y);
			}
		}
	}
    
    this->mapLength=1100;
    for(int m = 8; m >= 0; m--)
    {
        for(int n = 0;n < 2*MAX_NUM - 1;n++)
        {
            myVecRight = Vec2((7+m/2.0)*HORIZON_SPACE, (n/2.0+1)*VERTICAL_SPACE);
            //CCLOG("right: %f, %f" , myVecRight.x, myVecRight.y );
            //CCLOG("right level: m = %d, n = %d, value = %d" , m, n, level[m][n]);
            if (level[m][n] == 1)//∆’Õ®µ„
            { 
                PointInfo myPointRight;
                auto r= DrawNode::create();
                r->setAnchorPoint(Vec2(0.5,0.5));
                addChild(r, 2);
                r->setTag(this->mapLength);
                //r->drawDot(myVecRight, NORMAL_DOT_RADIUS, Color4F(0,0,0,1));
                myPointRight.tag = r->getTag();
                myPointRight.pos = myVecRight;
                myPointRight.isKeyPoint=0;
                myPointRight.flag = false;
                this->pointMapRight.insert(pair<int,PointInfo>(this->mapLength,myPointRight));
                this->mapLength++;
                
                //create star sprite
                auto starN = Sprite::create(P_NORMAL_IMG_NAME);
                starN->setScale(POINT_SCALE_FACTOR);
                starN->setPosition(myVecRight);
                starN->setAnchorPoint(Vec2(0.5, 0.5));
                this->addChild(starN, 3);
                
            }
            else if(level[m][n] == 3)//πÿº¸µ„
            {
                PointInfo myPointRight;
                this->keyPointNum++;
                CCLOG("init keyPointNum %d  " , keyPointNum);
                auto r= DrawNode::create();
                r->setAnchorPoint(Vec2(0.5,0.5));
                addChild(r, 2);
                r->setTag(this->mapLength);
                //r->drawDot(myVecRight, KEY_DOT_RADIUS, Color4F::BLUE);
                myPointRight.tag = r->getTag();
                myPointRight.pos = myVecRight;
                myPointRight.isKeyPoint=1;
                myPointRight.flag = false;
                this->pointMapRight.insert(pair<int,PointInfo>(this->mapLength,myPointRight));
                this->mapLength++;
                
                //create star sprite
                auto flag = Sprite::create(P_KEY_IMG_NAME);
                flag->setScale(POINT_SCALE_FACTOR);
                flag->setPosition(myVecRight);
                flag->setAnchorPoint(Vec2(0.5, 0.5));
                this->addChild(flag, 3);
                
            }
            else if(level[m][n] == 2)
            {
                auto r= DrawNode::create();
                r->setAnchorPoint(Vec2(0.5,0.5));
                addChild(r, 2);  
                //r->setTag(this->baffleTag);
                this->baffleList.push_front(myVecRight);
                //r->drawDot(myVecRight, KEY_DOT_RADIUS, Color4F::RED);
                //create baffle sprite
                if (m%2 == 0 && n%2 != 0) {
                    auto wood = Sprite::create(BAFFLE_H_IMG_NAME);
                    wood->setScale(BAFFLE_SCALE_FACTOR);
                    wood->setPosition(myVecRight);
                    wood->setAnchorPoint(Vec2(0.5, 0.5));
                    this->addChild(wood, 3);
                } else {
                    auto wood = Sprite::create(BAFFLE_V_IMG_NAME);
                    wood->setScale(BAFFLE_SCALE_FACTOR);
                    wood->setPosition(myVecRight);
                    wood->setAnchorPoint(Vec2(0.5, 0.5));
                    this->addChild(wood, 3);
                }

                CCLOG("r: x=%f, y=%f, width=%f, height=%f",r->getBoundingBox().origin.x, r->getBoundingBox().origin.y, r->getBoundingBox().size.width, r->getBoundingBox().size.height);
                this->baffleTag++;

            }
        }
    }
}


bool PointGame::isTouchPoint(Vec2 vec)
{
    if (this->getChildByTag(LEVEL_PAUSE_LAYER_TAG) || this->getChildByTag(LEVEL_PASS_LAYER_TAG)) {
        return false;
    }
    
	map<int,PointInfo>::iterator itor;

	if(!this->pointMapLeft.empty())
	{
		CCLOG("pointMap is not empty");
		itor=this->pointMapLeft.begin();
        CCLOG("touch x: %f, y: %f", vec.x, vec.y);
		while(itor!=this->pointMapLeft.end())
		{
				if(itor->second.flag!=1&&(vec.x>itor->second.pos.x-TOUCH_DIV&&vec.x<itor->second.pos.x+TOUCH_DIV&&vec.y>itor->second.pos.y-TOUCH_DIV&&vec.y<itor->second.pos.y+TOUCH_DIV))
                {
                    CCLOG("touch x: %f, y: %f", vec.x, vec.y);

                    if(this->leftPointTagList.empty())
                    {
                        itor->second.flag=1;
                        this->leftPointTagList.push_back(itor->second.tag);
                        if(pointMapRight.find(itor->second.tag+L_R_TAG_SAPCE)->second.isKeyPoint==1)
                        {
                            this->keyPointNum--;
                            CCLOG("isTouchPoint: first touch keynum = %d",this->keyPointNum);
                            int tag = itor->second.tag + LEFT_STAR_OFFSET;
                            changeImage(tag, P_KEY_IMG_NAME);
                            
                        } else {
                            int tag = itor->second.tag + LEFT_STAR_OFFSET;
                            changeImage(tag, P_HIGHLIGHT_IMG_NAME);
                        }

                    }else if(isNeighbor(this->pointMapLeft.find(this->leftPointTagList.back())->second.pos,itor->second.pos)) {
                        CCLOG("IS NEIGHBOR");
                        if (!canDrawLine(pointMapRight.find(leftPointTagList.back()+L_R_TAG_SAPCE)->second.pos,pointMapRight.find(itor->second.tag+L_R_TAG_SAPCE)->second.pos))
                        {
                            break;
                        }

                        drawLine(this->pointMapLeft.find(this->leftPointTagList.back())->second.pos,itor->second.pos,true);

                        drawLine(pointMapRight.find(leftPointTagList.back()+L_R_TAG_SAPCE)->second.pos,pointMapRight.find(itor->second.tag+L_R_TAG_SAPCE)->second.pos, false);
                        CCLOG("keypointnum %d",this->keyPointNum);
                        if(pointMapRight.find(itor->second.tag+L_R_TAG_SAPCE)->second.isKeyPoint==1)
                        {
                            this->keyPointNum--;
                            CCLOG("isTouchPoint: keynum = %d",this->keyPointNum);
                            int tag = itor->second.tag + LEFT_STAR_OFFSET;
                            changeImage(tag, P_KEY_IMG_NAME);
                        } else {
                            int tag = itor->second.tag + LEFT_STAR_OFFSET;
                            changeImage(tag, P_HIGHLIGHT_IMG_NAME);
                        }
                        if(this->keyPointNum<=0)
                        {
                            leverPass();
                        }
                        this->leftPointTagList.push_back(itor->second.tag);
                        itor->second.flag=1;

                        //…Ë÷√≈‹∂Øæ´¡È
                        addRunningSprite();
                    }	
                    itor++;
                    return true;
            }
			else
                itor++;
		}
		return false;
	}
	return false;
}

void PointGame::drawLine(Vec2 vec1,Vec2 vec2, bool isLeft)
{
    auto line = DrawNode::create();
    
    //line->drawSegment(vec1, vec2, 1, Color4F(0.0, 0.0, 1, 1));
    
    if(isLeft==1)
    {
        addChild(line, 1);
        line->setTag(this->leftLineTag);
        this->leftLineTagStack.push(this->leftLineTag);
        this->leftLineTag++;
        
        auto lightning = DrawLightning::create();
        if (vec1.y == vec2.y) {
            Size size = Size(HORIZON_SPACE, 3);
            lightning->setContentSize(size);
            lightning->ignoreAnchorPointForPosition(false);
            lightning->setAnchorPoint(Vec2(0.5, 0.5));
            lightning->setPosition((vec1.x+vec2.x)/2, vec1.y);
            lightning->setStartPoint(Vec2(0, size.height/2));
            lightning->setEndPoint(Vec2(size.width, size.height/2));
        } else {
            Size size = Size(3, VERTICAL_SPACE);
            lightning->setContentSize(size);
            lightning->ignoreAnchorPointForPosition(false);
            lightning->setAnchorPoint(Vec2(0.5, 0.5));
            lightning->setPosition(vec1.x, (vec1.y+vec2.y)/2);
            lightning->setStartPoint(Vec2(size.width/2, 0));
            lightning->setEndPoint(Vec2(size.width/2, size.height));
        }
        this->addChild(lightning, 2);
        
    } else if(isLeft==0) {
        line->setTag(this->rightLineTag);
        this->rightLineTagStack.push(this->rightLineTag);
        this->rightLineTag++;
    }	

}

void PointGame::getVecByTag(int tag, Vec2& point)
{
	PointInfo tmpPoint;
	tmpPoint=this->pointMapLeft.find(tag)->second;
	point.x = tmpPoint.pos.x;
	point.y = tmpPoint.pos.y;
}

bool  PointGame::canDrawLine(Vec2 vec1,Vec2 vec2)
{
    CCLOG("vec1: x=%f, y=%f", vec1.x, vec1.y);
    CCLOG("vec2: x=%f, y=%f",vec2.x, vec2.y);
    Rect *rect = PointGame::createLineRect(vec1, vec2);
    CCLOG("rect: x=%f, y=%f, width=%f, height=%f",rect->origin.x, rect->origin.y, rect->size.width, rect->size.height);
    
    list<Vec2>::iterator itor;
    itor=this->baffleList.begin();
    while(itor!=baffleList.end())
    {
        //DrawNode *baffle = (DrawNode *)this->getChildByTag(*itor++);
        CCLOG("baffle: x=%f, y=%f",itor->x,itor->y);
        if (rect->containsPoint(*itor))
        {
            CCLOG("collision!!!");
            delete rect;
            return false;
        }	
        itor++;
    }
    delete rect;
    return true;
}

Rect* PointGame::createLineRect(Vec2 vec1,Vec2 vec2)
{
	Vec2 startPoint;
	if (vec2.x > vec1.x || vec2.y > vec1.y)
	{
		startPoint = vec1;
	} else
	{
		startPoint = vec2;
	}
	float x = startPoint.x - 5 ;
	float y = startPoint.y - 5;
	float width;
	float height;
	if (abs(vec2.y - vec1.y) < 0.01)
	{
		width = (abs(vec1.x - vec2.x) > abs(vec1.y - vec2.y))?abs(vec1.x - vec2.x):abs(vec1.y - vec2.y) + 10;
		height = 10;
	} 
	else
	{
		width = 10;
		height = (abs(vec1.x - vec2.x) > abs(vec1.y - vec2.y))?abs(vec1.x - vec2.x):abs(vec1.y - vec2.y) + 10;
	}
	Rect *rect = new Rect(x, y, width, height);

	return rect;
}

bool  PointGame::isNeighbor(Vec2 vec1,Vec2 vec2)
{
	//CCLog("vec1 x: %f, y: %f", vec1.x, vec1.y);
	//CCLog("vec2 x: %f, y: %f", vec2.x, vec2.y);
	if(vec1.x==vec2.x&&(abs(abs(vec1.y-vec2.y)-VERTICAL_SPACE)<=1))
	{
		return true;
	}
	else if(vec1.y==vec2.y&&(abs(abs(vec1.x-vec2.x)-HORIZON_SPACE)<=1))
	{
		return true;
	}
	return false;
}

#pragma mark - Running sprite

void PointGame::update(float dt)
{
	if (this->getChildByTag(RUNNING_SPRITE_TAG) == NULL || this->leftPointTagList.size() < 2)
	{
		return;
	} 
	Sprite *sprite = (Sprite *)this->getChildByTag(RUNNING_SPRITE_TAG);
	Vec2 endPos;
	getVecByTag( this->leftPointTagList.back(), endPos);
	Vec2 curPos = sprite->getPosition();
	if (abs(curPos.x-endPos.x) < 0.01 && abs(curPos.y-endPos.y) < 0.01)
	{
		addRunningSprite();
	}

}

void PointGame::addRunningSprite(void)
{
	//CCLog("leftPointTagList size: %d",this->leftPointTagList.size());

	Sprite *sprite;
	if (this->getChildByTag(RUNNING_SPRITE_TAG) == NULL)
	{
		sprite = Sprite::create("UFO.png");
		sprite->setScale(UFO_SCALE_FACTOR);
		sprite->setTag(RUNNING_SPRITE_TAG);
		this->addChild(sprite, 2);
	} 
	else
	{
		sprite = (Sprite *)this->getChildByTag(RUNNING_SPRITE_TAG);
		sprite->stopAllActions();
	}
     
	Vector<FiniteTimeAction*>actions;
	list<int>::iterator itor = this->leftPointTagList.begin();
	Vec2 startPos;
	getVecByTag(*itor, startPos);
	sprite->setPosition(startPos);
	while (itor != this->leftPointTagList.end())
	{
		Vec2 tarPos;
		getVecByTag(*itor, tarPos);
		auto moveAction = MoveTo::create(0.5, tarPos);
		actions.pushBack(moveAction);
		itor++;
	}
	auto sequenceAction = Sequence::create(actions);
	//auto repeat = RepeatForever::create(sequenceAction);
	sprite->runAction(sequenceAction);

}

void PointGame::onTouchEnded(Touch* touch, Event *event)
{
	//Size visibleSize = Director::getInstance()->getVisibleSize;
	auto touchPoint = touch->getLocation();

	
	if (isTouchPoint(touchPoint))
	{
	}
}

void PointGame::spriteMoveFinished(Ref* pSender)  
{  
      
} 

#pragma mark - Callback functions

void PointGame::changeImage(int tag, const string& name)
{
    Sprite *sprite = (Sprite *)this->getChildByTag(tag);
    auto texture = Director::getInstance()->getTextureCache()->addImage(name);
    sprite->setTexture(texture);
    sprite->setOpacity(70);
    sprite->setScale(0.2);
    auto fadeAction = FadeIn::create(1);
    sprite->runAction(fadeAction);
}

void PointGame::revokeCallback(Ref* pSender)
{
	CCLOG("You pressed the revoke button");
    
    if (this->getChildByTag(LEVEL_PAUSE_LAYER_TAG) || this->getChildByTag(LEVEL_PASS_LAYER_TAG)) {
        return;
    }
    
    if(this->leftPointTagList.size()==1)
    {
        pointMapLeft.find(this->leftPointTagList.back())->second.flag=0;
		if(pointMapRight.find(this->leftPointTagList.back()+L_R_TAG_SAPCE)->second.isKeyPoint==1)
		{
			this->keyPointNum++;
		}
        int tag = this->leftPointTagList.back() + LEFT_STAR_OFFSET;
        Sprite *sprite = (Sprite *)this->getChildByTag(tag);
        auto texture = Director::getInstance()->getTextureCache()->addImage(P_NORMAL_IMG_NAME);
        sprite->setTexture(texture);
		this->leftPointTagList.pop_back();
		this->removeChildByTag(RUNNING_SPRITE_TAG);
    }
    
	if ((!this->leftLineTagStack.empty())&&(!this->rightLineTagStack.empty()))
	{
		CCLOG("go into revokeCallback");
		DrawNode *line = (DrawNode *)this->getChildByTag(this->leftLineTagStack.top());
		this->removeChild(line, true);
		line = (DrawNode *)this->getChildByTag(this->rightLineTagStack.top());
		this->removeChild(line, true);
		this->pointMapLeft.find(this->leftPointTagList.back())->second.flag=0;

	  //  CCLOG("current tag: %d x: %f y:%f", currentTouchPoint.tag,currentTouchPoint.pos.x,currentTouchPoint.pos.y);
		CCLOG("second.flag: %d", pointMapLeft.find(this->leftPointTagList.back())->second.flag);
		if(pointMapRight.find(this->leftPointTagList.back()+L_R_TAG_SAPCE)->second.isKeyPoint==1)
		{
			this->keyPointNum++;
			CCLOG("revokeCallback: keyPointNum = %d", keyPointNum);
		}
		this->leftLineTagStack.pop();
		this->rightLineTagStack.pop();
        int tag = this->leftPointTagList.back() + LEFT_STAR_OFFSET;
        Sprite *sprite = (Sprite *)this->getChildByTag(tag);
        auto texture = Director::getInstance()->getTextureCache()->addImage(P_NORMAL_IMG_NAME);
        sprite->setTexture(texture);
		this->leftPointTagList.pop_back();
	//	rightPointTagStack.pop();
		addRunningSprite();
	}
}

void PointGame::startLevelAgain(Ref* pSender)
{
    if (this->getChildByTag(LEVEL_PAUSE_LAYER_TAG) || this->getChildByTag(LEVEL_PASS_LAYER_TAG)) {
        return;
    }
    auto scene = PointGame::createScene();
    // run
    Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}

void PointGame::gamePause(Ref* pSender)
{
    if (this->getChildByTag(LEVEL_PAUSE_LAYER_TAG) || this->getChildByTag(LEVEL_PASS_LAYER_TAG)) {
        return;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto layer = LayerColor::create(Color4B(0,0,0,0), visibleSize.width, visibleSize.height);
    layer->setOpacity(170);
    layer->setTag(LEVEL_PAUSE_LAYER_TAG);
	this->addChild(layer, 5);
    
    //continue item
    auto continueItem = MenuItemFont::create("Continue", CC_CALLBACK_1(PointGame::gameContinue, this));
    continueItem->setFontSizeObj(50);
    continueItem->setFontNameObj("Marker Felt.ttf");
    continueItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + 100));
    //returnItem->setScale(RETURN_SCALE_FACTOR);
    continueItem->setAnchorPoint(Vec2(0.5, 0.5));
    
    //return to level choose
    auto returnItem = MenuItemFont::create("Select Level", CC_CALLBACK_1(PointGame::gameReturnToLevelChoose, this));
    returnItem->setFontSizeObj(50);
    returnItem->setFontNameObj("Marker Felt.ttf");
    returnItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    //returnItem->setScale(RETURN_SCALE_FACTOR);
    returnItem->setAnchorPoint(Vec2(0.5, 0.5));
    
    //return to main menu
    auto mainMenuItem = MenuItemFont::create("Main Menu", CC_CALLBACK_1(PointGame::gameReturnToMainMenu, this));
    mainMenuItem->setFontSizeObj(50);
    mainMenuItem->setFontNameObj("Marker Felt.ttf");
    mainMenuItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 100));
    //returnItem->setScale(RETURN_SCALE_FACTOR);
    mainMenuItem->setAnchorPoint(Vec2(0.5, 0.5));
    
    auto menu = Menu::create(continueItem, returnItem, mainMenuItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    layer->addChild(menu);
}

void PointGame::gameContinue(Ref* pSender)
{
    this->removeChildByTag(LEVEL_PAUSE_LAYER_TAG);
}

void PointGame::gameReturnToLevelChoose(Ref* pSender)
{
	auto scene = GameLevelChoose::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}

void PointGame::gameReturnToMainMenu(Ref* pSender)
{
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}

void PointGame::leverPass()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto layer = LayerColor::create(Color4B(0,0,0,0), visibleSize.width/2, visibleSize.height/2);
    layer->setOpacity(170);
    layer->setTag(LEVEL_PASS_LAYER_TAG);
    layer->ignoreAnchorPointForPosition(false);
    layer->setAnchorPoint(Vec2(0.5, 0.5));
    layer->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	this->addChild(layer, 5);
    
    Size layerSize = layer->getContentSize();
    float x = 0.0;
    float y = 0.0;
    //label
    auto label = Label::createWithTTF("Congratulations!", "Marker Felt.ttf", 60);
    label->setPosition(Vec2(x + layerSize.width/2, y + layerSize.height/2 + 70));
    label->setAnchorPoint(Vec2(0.5, 0.5));
    layer->addChild(label);
    //try again
    auto againItem = MenuItemFont::create("Try Again", CC_CALLBACK_1(PointGame::tryAgain, this));
    againItem->setFontSizeObj(40);
    againItem->setFontNameObj("Marker Felt.ttf");
    againItem->setPosition(Vec2(x + layerSize.width/2 - 120, y + layerSize.height/2 - 70));
    //returnItem->setScale(RETURN_SCALE_FACTOR);
    againItem->setAnchorPoint(Vec2(0.5, 0.5));
    
    //next level
    auto nextLevelItem = MenuItemFont::create("Next Level", CC_CALLBACK_1(PointGame::nextLevel, this));
    nextLevelItem->setFontSizeObj(40);
    nextLevelItem->setFontNameObj("Marker Felt.ttf");
    nextLevelItem->setPosition(Vec2(x + layerSize.width/2 + 120, y + layerSize.height/2 - 70));
    //returnItem->setScale(RETURN_SCALE_FACTOR);
    nextLevelItem->setAnchorPoint(Vec2(0.5, 0.5));
    
    auto menu = Menu::create(againItem, nextLevelItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    layer->addChild(menu);
}

void PointGame::tryAgain(Ref* pSender)
{
    auto scene = PointGame::createScene();
    // run
    Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}

void PointGame::nextLevel(Ref* pSender)
{
    if (this->curLevelIndex < MAX_LEVEL_NUM) {
        Constant::level = this->curLevelIndex + 1;
        auto scene = PointGame::createScene();
        // run
        Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
    }
}