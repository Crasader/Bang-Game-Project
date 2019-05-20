//
//  FriendScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/18.
//

#ifndef FriendScene_hpp
#define FriendScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <nlohmann/json.hpp>

enum class Search_Msg{
    Err, Success
};

class FriendScene : public cocos2d::Scene{
public:
    
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    
    CREATE_FUNC(FriendScene);
    
private:
    cocos2d::ui::EditBox *createEditBox(const std::string &PlaceHolder, const std::string &ImagePath);
    void BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void SearchCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    //--------------------------------------------
    cocos2d::Label *SearchMsgLabel(Search_Msg msg);
    cocos2d::Label *ErrMsgLabel();
    cocos2d::Label *SucMsgLabel();
    //--------------------------------------------
    static const std::string ErrMsg;//search friend error msg
    static const std::string SucMsg;//search friend success msg
};




#endif /* FriendScene_hpp */
