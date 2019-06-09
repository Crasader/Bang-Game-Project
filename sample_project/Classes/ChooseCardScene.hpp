//
//  ChooseCardScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/6.
//

#ifndef ChooseCardScene_hpp
#define ChooseCardScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameScene.hpp"

#include <vector>
#include <stdio.h>

class ChooseCardLayer : public cocos2d::Layer{
public:
    bool init() override;
    void update(float) override;
    
    void set_all(int chooser, int choosee, bool COD, std::vector<int>& cardlist);
    
    
    void set_ChooseOrDiscard(bool cod);
    bool get_ChooseOrDiscard() const;
    
    void set_should_dis_amount(int amount);
    void set_now_dis_amount(int amount);
    void set_state(int state);

    int chooser_ = -1;
    int choosee_ = -1;
    std::vector<int> cardList_;
    
    CREATE_FUNC(ChooseCardLayer);
    
    
    
    void cardCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType, int idx);
    //void DoNothingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    
private:
    
    int now_dis_amount_ = 0;
    int should_dis_amount_ = 0;
    
    int state_ = -1; // 0 end turn dis card , 
    
    bool ChooseOrDiscard;
    const cocos2d::Size  ButtonSize_ = cocos2d::Size(1546/4, 439/4);
    constexpr char static *fontpath_ = "fonts/arial_Bold.ttf";
    constexpr int static fontsize_ = 40;
};

#endif /* ChooseCardScene_hpp */
