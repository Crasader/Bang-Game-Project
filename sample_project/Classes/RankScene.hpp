//
//  RankScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/18.
//

#ifndef RankScene_hpp
#define RankScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class RankScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    
    CREATE_FUNC(RankScene);
    
private:
    void BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    
};


#endif /* RankScene_hpp */
