//
//  EndGameScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/10.
//

#include "EndGameScene.hpp"
#include "ClientSocket.hpp"
#include "LobbyScene.hpp"
#include "WrapInfo.hpp"

USING_NS_CC;



bool EndGameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->setContentSize(Size(3000/3, 1551/3 ));
    this->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2));
    
    //==================================================
    
    //add background
    auto BGsprite = Sprite::create("notification-bg.png");
    BGsprite->setContentSize(Size(3000/3, 1551/3 ));
    this->addChild(BGsprite);
    //==================================================
    
    
    auto OKbutton = ui::Button::create("ok-btn.png", "ok-btn-click.png", "ok-btn.png"); //472 x 358
    OKbutton->ignoreContentAdaptWithSize(false);
    OKbutton->setContentSize(Size(472/4, 358/4));
    OKbutton->setPosition(Vec2(300, -150));
    OKbutton->addClickEventListener(CC_CALLBACK_0(EndGameLayer::OkCallback ,this));
    this->addChild(OKbutton);
    
    
    return true;
}

void EndGameLayer::set_WinOrLose(WinAndLose WinOrLose){
    WorL_ = WinOrLose;
}

void EndGameLayer::updateInfo(){
    
    //Game over label
    Label* gameoverL;
    switch (WorL_) {
        case WinAndLose::WIN:{
            gameoverL = Label::createWithTTF(Win_, fontpath_, fontsize_);
            break;
        }
        case WinAndLose::LOSE:{
            gameoverL = Label::createWithTTF(Lose_, fontpath_, fontsize_);
            break;
        }
        default:
            break;
    }
    gameoverL->setColor(Color3B::BLACK);
    gameoverL->setPosition(Vec2(0, 150));
    this->addChild(gameoverL);
}

void EndGameLayer::OkCallback(){
    auto scene = LobbyScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
