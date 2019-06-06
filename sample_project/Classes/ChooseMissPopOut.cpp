//
//  ChooseMissPopOut.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/6.
//

#include "ChooseMissPopOut.hpp"
#include <iostream>
#include "ClientSocket.hpp"
#include "WrapInfo.hpp"
#include "GameScene.hpp"
USING_NS_CC;


bool MissLayer::init()
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
    
    auto topLabel = Label::createWithTTF("YOU WERE BANG!", fontpath_, 70);
    topLabel->setColor(Color3B::BLACK);
    topLabel->setPosition(0 , 150);
    this->addChild(topLabel);
    
    
    //Miss button
    auto missButton = ui::Button::create("notification-btn.png", "notification-btn-click.png","notification-btn.png");
    missButton->addTouchEventListener(CC_CALLBACK_2(MissLayer::MissCallback, this));
    missButton->ignoreContentAdaptWithSize(false);
    missButton->setContentSize(ButtonSize_);
    missButton->setPosition(Vec2(-200, 0));
    
    auto missLabel = Label::createWithTTF("Missed!", fontpath_, fontsize_);
    missLabel->setPosition(Vec2(missButton->getContentSize().width/2, missButton->getContentSize().height/2 - 5));
    missButton->addChild(missLabel);
    this->addChild(missButton);
    
    //Do Nothing button
    //Miss menu item
    auto doNothingButton = ui::Button::create("donothing-btn.png", "donothing-btn-click.png","donothing-btn.png");
    doNothingButton->addTouchEventListener(CC_CALLBACK_2(MissLayer::DoNothingCallback, this));
    doNothingButton->ignoreContentAdaptWithSize(false);
    doNothingButton->setContentSize(ButtonSize_);
    doNothingButton->setPosition(Vec2(200, 0));
    this->addChild(doNothingButton);
    
    
    return true;
}

void MissLayer::MissCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:{
            auto client = CClientSocket::getInstance();
            client->sendMessage(WrapInfo::WrapUseMissed(true));
            
            GameScene::getInstance()->set_action(-1);
            
            break;
        }
            
            
            
        default:
            break;
    }
}

void MissLayer::DoNothingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:{
            auto client = CClientSocket::getInstance();
            client->sendMessage(WrapInfo::WrapUseMissed(true));
            
            GameScene::getInstance()->set_action(-1);
            break;
        }
            
        default:
            break;
    }
}
