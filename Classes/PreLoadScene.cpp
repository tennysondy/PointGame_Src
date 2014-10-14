//
//  PreLoadScene.cpp
//  PointGame
//
//  Created by 丁 一 on 14-10-14.
//
//

#include "PreLoadScene.h"
#include "Constant.h"
#include "PointGameScene.h"

Scene* PreLoadScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	//auto layer = LayerColor::create(Color4B(255,255,0,111));
	auto layer = PreLoadScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool PreLoadScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto layer = LayerColor::create(Color4B(255,255,255,255));
	this->addChild(layer, 0);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    string a = "第 ";
    string index = to_string(Constant::level);
    string b = " 关";
    string text = a+index+b;
    auto title = LabelTTF::create(text, "Arial", 100);
	title->setColor(Color3B::BLACK);
    // position the label on the center of the screen
    title->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    
    // add the label as a child to this layer
	this->addChild(title, 1);
    
    return true;
}

void PreLoadScene::onEnter()
{
    //auto scene = PointGame::createScene();
    //Director::getInstance()->replaceScene(TransitionFade::create(1,scene));

}

void PreLoadScene::onEnterTransitionDidFinish()
{
    //Layer::onEnterTransitionDidFinish();
    auto scene = PointGame::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1,scene));
}
