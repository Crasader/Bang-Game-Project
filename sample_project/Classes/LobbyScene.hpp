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
#include <nlohmann/json.hpp>

#include "User.hpp"
#include "NetworkCom.hpp"

class LobbyScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    CREATE_FUNC(LobbyScene);
    
    void getInfoFromServer(){
        
        auto client = Client::getInstance();
        auto user = User::getInstance();
        
        json rec = client->userRegisterLogin(user->getUID());
        
        CCLOG(rec.dump().c_str());
        
        if(rec["Nick Name"] == ""){
            client->userChangenickname("Test Name");
            rec = client->userRegisterLogin(user->getUID());
        }
        
        user->setMoney(rec["User Money"]);
        user->setNickName(rec["Nick Name"]);
        user->setWin(rec["User Win"]);
        user->setLose(rec["User Lose"]);
        
        
    }

    
    
private:
    cocos2d::ui::Button *createButton(
                                      bool buttonEnabled, const std::string& buttonTitleText,
                                      const cocos2d::Color3B& buttonColor, const std::string& ImagePath1,const  std::string& ImagePath2, const std::string& ImagePath3);
    void SettingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void RankCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void FriendCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    using json = nlohmann::json;
    json request_info, r2;
    
    float nextYPosition;
};




#endif /* LobbyScene_hpp */
