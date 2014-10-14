//
//  PreLoadScene.h
//  PointGame
//
//  Created by 丁 一 on 14-10-14.
//
//

#ifndef __PointGame__PreLoadScene__
#define __PointGame__PreLoadScene__

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class PreLoadScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    CREATE_FUNC(PreLoadScene);
};

#endif /* defined(__PointGame__PreLoadScene__) */
