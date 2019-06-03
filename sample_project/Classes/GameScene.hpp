//
//  GameScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/3.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"



class PlayerHead : public cocos2d::Sprite{
public:
    static PlayerHead * create();
    /*
    PlayerHead(const std::string username, const std::string charName, int hp, int team);
    PlayerHead();
    */
    int get_hp() const;
    int get_team() const;
    bool is_Jail() const;
    
    void set_username(const std::string username);
    void set_charName(const std::string charName);
    void set_hp(int hp);
    void set_team(int team);
    void set_Jail(bool isJail);
    
    void updataInfo(const std::string username, const std::string charName, int hp, int team, bool isJail);
    void init(const std::string username, const std::string charName, int hp, int team, bool isJail);
    
private:
    const int static fontSize = 25;
    constexpr char static *fontpath = "fonts/arial.ttf";
    
    cocos2d::Sprite * JailL = nullptr;
    cocos2d::Label * usernameL = nullptr;
    cocos2d::Label * charNameL = nullptr;
    cocos2d::Label * hpL = nullptr;
    
    std::string username_ = "username";
    std::string charName_ = "character";
    int hp_ = 0;
    int team_ = -1;
    bool isJail_ = false;
    
    
};

//================Game Sacen======================
class GameScene : public cocos2d::Scene{
public:
    
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    CREATE_FUNC(GameScene);
    
    
    
    
private:
    PlayerHead *ShowPlayer[6] = {};
    int myHP_ = 0;
    
};
#endif /* GameScene_hpp */
