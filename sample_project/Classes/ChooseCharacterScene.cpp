//
//  ChooseCharacterScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/1.
//

#include "ChooseCharacterScene.hpp"
#include "NetworkCom.hpp"
#include "WrapInfo.hpp"
#include "GameScene.hpp"
#include <thread>

USING_NS_CC;
std::string ChooseCharacterScene::CH_name0_ = "";
std::string ChooseCharacterScene::CH_name1_ = "";

void ChooseCharacterScene::SetCharacterName(const std::string & Name1, const std::string & Name2)
{
    CH_name0_ = Name1;
    CH_name1_ = Name2;
}

void ChooseCharacterScene::ListenerStartGame(){
    CClientSocket::getInstance()->busyWaitting(7);
    isStart = true;
}

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
    std::thread tThread(&ChooseCharacterScene::ListenerStartGame, this);
    tThread.detach();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //add backbround
    auto backGroundColor = CCLayerColor::create(ccc4(236, 207, 177, 255)); //RGBA
    this->addChild(backGroundColor, 0);
    
    //==============================================================================================================
    
    
    //Click to choose your character
    auto TopLogo = Sprite::create("click-logo.png");//1000 x 78
    TopLogo->setContentSize(Size(1000, 78));
    TopLogo->setPosition(Vec2(visibleSize.width/2, visibleSize.height-100));
    this->addChild(TopLogo);
    
    const int Button_y_pos = visibleSize.height/2 - 50;
    
    
    auto leftCH = Sprite::create("card-character.png"); //1029 x 1442
    leftCH->setContentSize(Size(1029/4, 1442/4));
    leftCH->setPosition(Vec2(2241/8, 2406/8 + 50));
    
    auto CH_label1 = Label::createWithTTF(CH_name0_, "fonts/arial.ttf", 30);
    CH_label1->setPosition(1024/8, 1442/4-50);
    CH_label1->setColor(Color3B::BLACK);
    
    leftCH->addChild(CH_label1);
    
    //this->addChild(leftCH);
    
    auto rightCH = Sprite::create("card-character.png");
    rightCH->setContentSize(Size(1029/4, 1442/4));
    rightCH->setPosition(Vec2(2241/8, 2406/8 + 50));
    
    auto CH_label2 = Label::createWithTTF(CH_name1_, "fonts/arial.ttf", 30);
    CH_label2->setPosition(1024/8, 1442/4-50);
    CH_label2->setColor(Color3B::BLACK);
    rightCH->addChild(CH_label2);
    
    //this->addChild(rightCH);
    
    
    leftButton = ui::Button::create("choose-bg-orange.png", "choose-bg-orange-click.png", "choose-bg-orange-click.png");//2241 x 2406
    leftButton->ignoreContentAdaptWithSize(false);
    leftButton->setContentSize(Size(2241/4, 2406/4));
    leftButton->setPosition(Vec2(visibleSize.width/2 -275, Button_y_pos));
    leftButton->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::LeftCallback, this));
    leftButton->addChild(leftCH);
    this->addChild(leftButton);
    
    
    
    
    rightButton = ui::Button::create("choose-bg-purple.png", "choose-bg-purple-click.png", "choose-bg-purple-click.png");//2241 x 2406
    rightButton->ignoreContentAdaptWithSize(false);
    rightButton->setContentSize(Size(2241/4, 2406/4));
    rightButton->setPosition(Vec2(visibleSize.width/2 +275, Button_y_pos));
    rightButton->addTouchEventListener(CC_CALLBACK_2(ChooseCharacterScene::RightCallback, this));
    rightButton->addChild(rightCH);
    this->addChild(rightButton);
    
    // Schedule the update method for this scene.
    this->scheduleUpdate();
    
    return true;
}

void ChooseCharacterScene::update(float){
    if(isStart){
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
}
void ChooseCharacterScene::LeftCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            std::thread tThread([this](){
                auto client = Client::getInstance();
                CClientSocket::getInstance()->sendMessage(WrapInfo::WrapChooseCharacter(this->CH_name0_).dump());
            });
            tThread.join();
            
            leftButton->setEnabled(false);
            rightButton->setEnabled(false);
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
                CClientSocket::getInstance()->sendMessage(WrapInfo::WrapChooseCharacter(this->CH_name1_).dump());
            });
            tThread.join();
            leftButton->setEnabled(false);
            rightButton->setEnabled(false);
            break;
        }
            
        default:
            break;
        }
}
