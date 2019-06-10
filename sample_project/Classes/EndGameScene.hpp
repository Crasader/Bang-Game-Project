//
//  EndGameScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/10.
//

#ifndef EndGameScene_hpp
#define EndGameScene_hpp

#include <stdio.h>
#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

enum class WinAndLose{
    WIN, LOSE
};

class EndGameLayer : public cocos2d::Layer{
public:
    bool init() override;
    //void update(float) override;
    
    
    CREATE_FUNC(EndGameLayer);
    
    void set_WinOrLose(WinAndLose WinOrLose);
    void updateInfo();
    void OkCallback();
    
    
private:
    
    WinAndLose WorL_ = WinAndLose::WIN;
    
    const std::string Win_ = "GAME OVER! YOU WIN!";
    const std::string Lose_ = "GAME OVER! YOU LOSE!";
    const char * fontpath_ = "fonts/arial_Bold.ttf";
    const int fontsize_ = 70;
    
};


#endif /* EndGameScene_hpp */
