//
//  LobbyScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/22.
//

#ifndef LobbyScene_hpp
#define LobbyScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class LobbyScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    CREATE_FUNC(LobbyScene);
    
private:
    cocos2d::ui::Button *createButton(
                                      bool buttonEnabled, const std::string& buttonTitleText,
                                      const cocos2d::Color3B& buttonColor, const std::string& ImagePath1,const  std::string& ImagePath2, const std::string& ImagePath3);
    
    void SettingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void RankCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void FriendCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    
    
    float nextYPosition;
};




#endif /* LobbyScene_hpp */
