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

USING_NS_CC;
//PointInfo currentTouchPoint;
//PointInfo currentTouchPointCurrent;
using namespace std;
using namespace CocosDenshion;

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
    auto layer = LayerColor::create(Color4B(255,255,204,255));
	this->addChild(layer, 0);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//currentTouchPoint.pos.x=-1;
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(PointGame::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, nullptr);
   menu->setPosition(Vec2::ZERO);
   this->addChild(menu, 1);

	auto revokeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										CC_CALLBACK_1(PointGame::revokeCallback,this));
	revokeItem->setPosition(Vec2(10*HORIZON_SPACE,5.5*VERTICAL_SPACE));
	auto menu1 = Menu::create(revokeItem, nullptr);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

	//ÃÌº”∑µªÿπÿø®—°‘Ò∞¥≈•
	auto homeItem = MenuItemImage::create("homeItemNormal.png",
		"homeItemLight.png",
		CC_CALLBACK_1(PointGame::backToChooseLevel, this));
	homeItem->setPosition(Vec2( -4*HORIZON_SPACE ,
		2.5*VERTICAL_SPACE));
	auto menuHome = Menu::create(homeItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menuHome, 1);

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
    string a = "第";
    string index = to_string(this->curLevelIndex);
    string b = "关";
    string text = a+index+b;
    auto title = LabelTTF::create(text, "Arial", 36);
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

				this->pointMapLeft.insert(pair<int,PointInfo>(this->mapLength,myPointLeft));
                
                //create star sprite
                auto texture = Director::getInstance()->getTextureCache()->addImage("star.png");
                auto star = Sprite::createWithTexture(texture);
                star->setScale(STAR_SCALE_FACTOR);
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
                r->drawDot(myVecRight, NORMAL_DOT_RADIUS, Color4F(0,0,0,1));
                myPointRight.tag = r->getTag();
                myPointRight.pos = myVecRight;
                this->pointMapRight.insert(pair<int,PointInfo>(this->mapLength,myPointRight));
                this->mapLength++;
            }
            else if(level[m][n] == 3)//πÿº¸µ„
            {
                PointInfo myPointRight;
                this->keyPointNum++;
                CCLOG("init keyPointNum %d  " , keyPointNum);
                auto r= DrawNode::create();
                r->setAnchorPoint(Vec2(0.5,0.5));
                addChild(r, 2);  
                r->drawDot(myVecRight, KEY_DOT_RADIUS, Color4F::BLUE);
                myPointRight.tag = r->getTag();
                myPointRight.pos = myVecRight;
                myPointRight.isKeyPoint=1;
                this->pointMapRight.insert(pair<int,PointInfo>(this->mapLength,myPointRight));
                this->mapLength++;
            }
            else if(level[m][n] == 2)
            {
                auto r= DrawNode::create();
                r->setAnchorPoint(Vec2(0.5,0.5));
                addChild(r, 2);  
                //r->setTag(this->baffleTag);
                this->baffleList.push_front(myVecRight);
                r->drawDot(myVecRight, KEY_DOT_RADIUS, Color4F::RED);

                CCLOG("r: x=%f, y=%f, width=%f, height=%f",r->getBoundingBox().origin.x, r->getBoundingBox().origin.y, r->getBoundingBox().size.width, r->getBoundingBox().size.height);
                this->baffleTag++;

            }
        }
    }
}


bool PointGame::isTouchPoint(Vec2 vec)
{
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
                            changeImage(tag, "flag.png");
                            
                        } else {
                            int tag = itor->second.tag + LEFT_STAR_OFFSET;
                            changeImage(tag, "starSelected.png");
                        }

                    }else if(isNeighbor(this->pointMapLeft.find(this->leftPointTagList.back())->second.pos,itor->second.pos)) {
                        CCLOG("IS NEIGHBOR");
                        if (!canDrawLine(pointMapRight.find(leftPointTagList.back()+L_R_TAG_SAPCE)->second.pos,pointMapRight.find(itor->second.tag+L_R_TAG_SAPCE)->second.pos))
                        {
                            break;
                        }
                        //»Áπ˚ø…“‘ª≠œﬂ£¨Ω´µ±«∞µ„—π’ª
                        drawLine(this->pointMapLeft.find(this->leftPointTagList.back())->second.pos,itor->second.pos,true);
                        //◊Û≤‡ª≠œﬂµƒÕ¨ ±‘⁄”“≤‡∂‘”¶Œª÷√ª≠œﬂ°£
                        drawLine(pointMapRight.find(leftPointTagList.back()+L_R_TAG_SAPCE)->second.pos,pointMapRight.find(itor->second.tag+L_R_TAG_SAPCE)->second.pos, false);
                        CCLOG("keypointnum %d",this->keyPointNum);
                        if(pointMapRight.find(itor->second.tag+L_R_TAG_SAPCE)->second.isKeyPoint==1)
                        {
                            this->keyPointNum--;
                            CCLOG("isTouchPoint: keynum = %d",this->keyPointNum);
                            int tag = itor->second.tag + LEFT_STAR_OFFSET;
                            changeImage(tag, "flag.png");
                        } else {
                            int tag = itor->second.tag + LEFT_STAR_OFFSET;
                            changeImage(tag, "starSelected.png");
                        }
                        if(this->keyPointNum<=0)
                        {
                            menuCloseCallback(nullptr);
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
//¡Ωµ„¡¨œﬂ
void PointGame::drawLine(Vec2 vec1,Vec2 vec2, bool isLeft){
		//ccDrawLine(ccp(vec1.x,vec1.y), ccp(vec2.x,vec2.y));
		auto line = DrawNode::create();

	//	line->drawSegment(vec1, vec2, 2, Color4F::RED);
		
		line->drawSegment(vec1, vec2, 2, Color4F(0.6,0.8,1, 1));
		
		if(isLeft==1)
		{
			addChild(line, 1);
			line->setTag(this->leftLineTag);
			this->leftLineTagStack.push(this->leftLineTag);
			this->leftLineTag++;

		}else if(isLeft==0)
		{
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
		//»Áπ˚yœ‡µ»£¨æÿ–Œ∫·◊≈ª≠
		width = (abs(vec1.x - vec2.x) > abs(vec1.y - vec2.y))?abs(vec1.x - vec2.x):abs(vec1.y - vec2.y) + 10;
		height = 10;
	} 
	else
	{
		//»Áπ˚y≤ªœ‡µ»£¨æÿ–Œ ˙◊≈ª≠
		width = 10;
		height = (abs(vec1.x - vec2.x) > abs(vec1.y - vec2.y))?abs(vec1.x - vec2.x):abs(vec1.y - vec2.y) + 10;
	}
	Rect *rect = new Rect(x, y, width, height);

	return rect;
}

//≈–∂œ¡Ωµ„ «∑Òœ‡¡⁄
bool  PointGame::isNeighbor(Vec2 vec1,Vec2 vec2){
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
	//…Ë÷√≈‹∂Øæ´¡È
	Sprite *sprite;
	if (this->getChildByTag(RUNNING_SPRITE_TAG) == NULL)
	{
		sprite = Sprite::create("UFO.png");
		sprite->setScale(UFO_SCALE_FACTOR);
		sprite->setTag(RUNNING_SPRITE_TAG);
		this->addChild(sprite, 10);
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


void PointGame::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    //Director::getInstance()->end();
	if (this->curLevelIndex < MAX_LEVEL_NUM)
	{
		auto scene = PointGame::createScene();
        Constant::level = this->curLevelIndex + 1;
		// run
		Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
	}

/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
*/
}

void PointGame::revokeCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the revoke button. Windows Store Apps do not implement a close button.","Alert");
	CCLOG();
    return;
#endif
	CCLOG("You pressed the revoke button");
    
    if(this->leftPointTagList.size()==1)
    {
        pointMapLeft.find(this->leftPointTagList.back())->second.flag=0;
		if(pointMapRight.find(this->leftPointTagList.back()+L_R_TAG_SAPCE)->second.isKeyPoint==1)
		{
			this->keyPointNum++;
		}
        int tag = this->leftPointTagList.back() + LEFT_STAR_OFFSET;
        Sprite *sprite = (Sprite *)this->getChildByTag(tag);
        auto texture = Director::getInstance()->getTextureCache()->addImage("star.png");
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
        auto texture = Director::getInstance()->getTextureCache()->addImage("star.png");
        sprite->setTexture(texture);
		this->leftPointTagList.pop_back();
	//	rightPointTagStack.pop();
		addRunningSprite();
	}
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
*/
}

void PointGame::backToChooseLevel(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the revoke button. Windows Store Apps do not implement a close button.","Alert");
	CCLOG();
    return;
#endif
	auto scene = GameLevelChoose::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
*/
}

void PointGame::changeImage(int tag, const string& name)
{
    Sprite *sprite = (Sprite *)this->getChildByTag(tag);
    auto texture = Director::getInstance()->getTextureCache()->addImage(name);
    sprite->setTexture(texture);
    sprite->setOpacity(70);
    auto fadeAction = FadeIn::create(1);
    sprite->runAction(fadeAction);
}
