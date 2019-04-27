//
//  SettingScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/25.
//

#ifndef SettingScene_hpp
#define SettingScene_hpp


#include "cocos2d.h"
#include "ui/CocosGUI.h"

class SettingScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    
    
    
    
    CREATE_FUNC(SettingScene);
    
private:
    void BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    cocos2d::ui::Button *createButton(
                                      bool buttonEnabled, const std::string& buttonTitleText,
                                      const cocos2d::Color3B& buttonColor, const std::string& ImagePath1,const  std::string& ImagePath2, const std::string& ImagePath3);
    float nextYPosition;
};

#endif /* SettingScene_hpp */
