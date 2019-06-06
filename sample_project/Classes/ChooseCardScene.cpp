//
//  ChooseCardScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/6.
//

#include "ChooseCardScene.hpp"
#include "ClientSocket.hpp"
#include "Card.hpp"
#include "WrapInfo.hpp"
#include <iostream>

USING_NS_CC;

//1000 x 517
float card_pos(int pos, int n){
    // 257 一張卡
    float edge = -300;
    float delta = 300;
    return edge + pos*delta;
}

bool ChooseCardLayer::init()
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
    
    CardButton * cardbutton[10];
    
    for(int i=0; i<cardList_.size(); i++){
        int cardID = cardList_[i];
        auto cardDB = CardDatabase::getInstance();
        auto card = cardDB->get_Card_byID(cardID);
        
        cardbutton[i] = CardButton::create(CardColor::BLUE);
        cardbutton[i]->setPosition(Vec2(card_pos(i, 3), 0));
        cardbutton[i]->my_init(card->get_cardName(), card->get_number(), card->get_suit());
        cardbutton[i]->addTouchEventListener(CC_CALLBACK_2(ChooseCardLayer::cardCallback, this, i));
        
        this->addChild(cardbutton[i], 0);
    }
     
    
    return true;
}

void ChooseCardLayer::set_all(int chooser, int choosee, bool COD, std::vector<int>& cardlist){
    chooser_ = chooser;
    choosee_ = choosee;
    ChooseOrDiscard = COD;
    cardList_ = cardlist;
}


void ChooseCardLayer::set_ChooseOrDiscard(bool cod){
    ChooseOrDiscard = cod;
}
bool ChooseCardLayer::get_ChooseOrDiscard() const{
    return ChooseOrDiscard;
}

void ChooseCardLayer::cardCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type, int idx){
    switch(type){
        case cocos2d::ui::Widget::TouchEventType::BEGAN:{
            auto client = CClientSocket::getInstance();
            client->sendMessage(WrapInfo::WrapChooseCard(cardList_[idx], chooser_, choosee_, ChooseOrDiscard));
            
            break;
        }
        default:
            break;
    }
}
