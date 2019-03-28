//
//  MenuScene.cpp
//  MyCppGame-mobile
//
//  Created by Guan Ying Chen on 2019/3/28.
//
#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto Title = Label::createWithTTF("Bang!", "fonts/Marker Felt.ttf", 150);
    if (Title == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        Title->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - Title->getContentSize().height));
        
        // add the label as a child to this layer
        this->addChild(Title, 1);
    }
    
   
    
    // Standard method to create a MenuItem
    
    auto starMenu = Menu::create();//Creat a Menu object
    starMenu->setPosition(Vec2(1334/2, 750/2));
    //std::cerr<<"Gary "<<Vec2::ZERO.x<<Vec2::ZERO.y<<std::endl;
    
    auto starMenuItem = Label::createWithSystemFont("開始", "Arial",  80);
    
    auto menuItemLabel = MenuItemLabel::create(starMenuItem,CC_CALLBACK_1(MenuScene::starMenuCallback,this));
    menuItemLabel->setPosition(Vec2::ZERO);
    
    starMenu->addChild(menuItemLabel);
    
    this->addChild(starMenu, 0);
    
    return true;
}

void MenuScene::starMenuCallback(cocos2d::Ref* pSender)
{
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}
