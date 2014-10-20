//
//  DrawLightning.h
//  PointGame
//
//  Created by 丁 一 on 14-10-16.
//
//

#ifndef __PointGame__DrawLightning__
#define __PointGame__DrawLightning__

#include <iostream>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class DrawLightning : public cocos2d::Layer
{
public:
    virtual bool init();
    virtual void onEnter();
    virtual void draw(Renderer* renderer, const Mat4 &transform, uint32_t flags);
    void drawLightning(Vec2& startPoint, Vec2& endPoint, float displace);
    CREATE_FUNC(DrawLightning);
    
    void setStartPoint(const Vec2& startPoint);
    void setEndPoint(const Vec2& endPoint);
    
protected:
    void onDraw(const Mat4 &transform, uint32_t flags);
    CustomCommand _customCommand;
private:
    Vec2 _startPoint;
    Vec2 _endPoint;
    float curDetail;
};

#endif /* defined(__PointGame__DrawLightning__) */
