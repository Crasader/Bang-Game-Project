//
//  ChooseCharacterScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/1.
//

#ifndef ChooseCharacterScene_hpp
#define ChooseCharacterScene_hpp

#include <stdio.h>
#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ChooseCharacterScene : public cocos2d::Scene{
public:
    
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    static void SetCharacterName(const std::string & Name1, const std::string & Name2);
    CREATE_FUNC(ChooseCharacterScene);
    
    void update(float) override;
    
    void ListenerStartGame();
    
private:
    bool isStart = false;
    cocos2d::ui::Button *leftButton = nullptr, *rightButton = nullptr;
    static std::string CH_name0_, CH_name1_;
    void LeftCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void RightCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
};


#endif /* ChooseCharacterScene_hpp */
