//
//  DrawLightning.cpp
//  PointGame
//
//  Created by 丁 一 on 14-10-16.
//
//

#include "DrawLightning.h"

using namespace std;
USING_NS_CC;

bool DrawLightning::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->curDetail = 5;
    
    return true;
}

void DrawLightning::onEnter()
{
    Layer::onEnter();
    
}

void DrawLightning::setStartPoint(const Vec2& startPoint)
{
    this->_startPoint = startPoint;
}

void DrawLightning::setEndPoint(const Vec2& endPoint)
{
    this->_endPoint = endPoint;
}

void DrawLightning::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawLightning::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void DrawLightning::onDraw(const Mat4 &transform, uint32_t flags)
{
    Director *director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    CHECK_GL_ERROR_DEBUG();
    
    float factor = CCRANDOM_0_1();
    if (factor < 0.5) {
        DrawPrimitives::setDrawColor4F(1.0, 1.0, 1.0, 1.0);
    } else {
        DrawPrimitives::setDrawColor4F(109.0/255.0, 158.0/255.0, 235/255.0, 1.0);
    }
    
    glLineWidth(2.0);
    drawLightning(this->_startPoint, this->_endPoint, 40);
    
    CHECK_GL_ERROR_DEBUG();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    
}

void DrawLightning::drawLightning(Vec2& startPoint, Vec2& endPoint, float displace)
{
    if(displace < curDetail){
        DrawPrimitives::drawLine(startPoint, endPoint);
    } else {
        float x1 = startPoint.x;
        float y1 = startPoint.y;
        float x2 = endPoint.x;
        float y2 = endPoint.y;
        
        float mid_x = (x2+x1) / 2;
        float mid_y = (y2+y1) / 2;
        mid_x += (CCRANDOM_0_1() -.5)*displace;
        mid_y += (CCRANDOM_0_1() -.5)*displace;
        
        Vec2 midPoint = Vec2(mid_x, mid_y);
        
        drawLightning(startPoint, midPoint, displace/2);
        drawLightning(endPoint, midPoint, displace/2);
    }
}