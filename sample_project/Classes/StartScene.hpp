//
//  StartScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/1.
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include <iostream>
#include "cocos2d.h"


class StartScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    void Login_callback();
    //void update(float delta) override;
    
    void menuCloseAppCallback(cocos2d::Ref *pSender);
    
    CREATE_FUNC(StartScene);

};

#endif /* StartScene_hpp */
