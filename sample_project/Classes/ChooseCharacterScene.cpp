//
//  ChooseCharacterScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/1.
//

#include "ChooseCharacterScene.hpp"
#include "NetworkCom.hpp"
#include <thread>

USING_NS_CC;


Scene *ChooseCharacterScene::createScene(){
    return ChooseCharacterScene::create();
}

// on "init" you need to initialize your instance
bool ChooseCharacterScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //add backbround
    auto backGroundColor = CCLayerColor::create(ccc4(236, 207, 177, 255)); //RGBA
    this->addChild(backGroundColor);
    
    //==============================================================================================================
    auto client = Client::getInstance();
    //json CH_info = client->getJBuffer();
    
    //CH_name0_ = CH_info["Character Name 0"], CH_name1_ = CH_info["Character Name 0"];
    
    //Click to choose your character
    auto TopLogo = Sprite::create("click-logo.png");//1000 x 78
    TopLogo->setContentSize(Size(1000, 78));
    TopLogo->setPosition(Vec2(visibleSize.width/2, visibleSize.height-100));
    this->addChild(TopLogo);
    
    const int Button_y_pos = visibleSize.height/2 - 50;
    
    auto leftCH = Sprite::create("card-character.png"); //1029 x 1442
    leftCH->setContentSize(Size(1029/4, 1442/4));
    auto CH_label1 = Label::createWithTTF("TEST0", "fonts/arial.ttf", 30);
    leftCH->addChild(CH_label1);
    CH_label1->setPosition(1024/8, 1442/4-50);
    CH_label1->setColor(Color3B::BLACK);
    
    auto rightCH = Sprite::create("card-character.png");
    rightCH->setContentSize(Size(1029/4, 1442/4));
    auto CH_label2 = Label::createWithTTF("TEST1", "fonts/arial.ttf", 30);
    rightCH->addChild(CH_label2);
    CH_label2->setPosition(1024/8, 1442/4-50);
    CH_label2->setColor(Color3B::BLACK);
    
    
    auto leftButton = ui::Button::create("choose-bg-orange.png", "choose-bg-orange-click.png", "choose-bg-orange.png");//2241 x 2406
    leftButton->ignoreContentAdaptWithSize(false);
    leftButton->setContentSize(Size(2241/4, 2406/4));
    leftButton->setPosition(Vec2(visibleSize.width/2 -275, Button_y_pos));
    leftButton->addChild(leftCH);
    leftCH->setPosition(Vec2(2241/8, 2406/8 + 50));
    leftButton->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::LeftCallback, this));
    this->addChild(leftButton);
    
    
    
    
    auto rightButton = ui::Button::create("choose-bg-purple.png", "choose-bg-purple-click.png", "choose-bg-purple.png");//2241 x 2406
    rightButton->ignoreContentAdaptWithSize(false);
    rightButton->setContentSize(Size(2241/4, 2406/4));
    rightButton->setPosition(Vec2(visibleSize.width/2 +275, Button_y_pos));
    rightButton->addChild(rightCH);
    rightCH->setPosition(Vec2(2241/8, 2406/8 + 50));
    rightButton->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::RightCallback, this));
    this->addChild(rightButton);
    
    
    return true;
}

void ChooseCharacterScene::LeftCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            std::thread tThread([this](){
                auto client = Client::getInstance();
                client->playerChoosecharacter(this->CH_name0_);
            });
            tThread.join();
            break;
        }
        default:
            break;
    }
    
}
void ChooseCharacterScene::RightCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            std::thread tThread([this](){
                auto client = Client::getInstance();
                client->playerChoosecharacter(this->CH_name1_);
            });
            tThread.join();
            break;
        }
            
        default:
            break;
        }
}
