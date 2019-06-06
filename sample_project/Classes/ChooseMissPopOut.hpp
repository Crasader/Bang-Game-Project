//
//  ChooseMissPopOut.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/6.
//

#ifndef ChooseMissPopOut_hpp
#define ChooseMissPopOut_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <stdio.h>

class MissLayer : public cocos2d::Layer{
public:
    bool init() override;
    CREATE_FUNC(MissLayer);
    
    void MissCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void DoNothingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);

private:
    const cocos2d::Size  ButtonSize_ = cocos2d::Size(1546/4, 439/4);
    constexpr char static *fontpath_ = "fonts/arial_Bold.ttf";
    constexpr int static fontsize_ = 40;
};

#endif /* ChooseMissPopOut_hpp */
