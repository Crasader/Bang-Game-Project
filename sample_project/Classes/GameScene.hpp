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
#include <iostream>
#include "ChooseMissPopOut.hpp"
#include "ChooseCardScene.hpp"
#include "EndGameScene.hpp"

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
    int get_position() const;
    
    void set_username(const std::string username);
    void set_charName(const std::string charName);
    void set_hp(int hp);
    void set_team(int team);
    void set_Jail(bool isJail);
    
    void updataInfo(const std::string username, const std::string charName, int hp, int team, bool isJail);
    void init(const std::string username, const std::string charName, int hp, int team, bool isJail, int position);
    void set_selectVisiable(bool visiable);
    
    void SelectButtonCallback();
    
    void update(float delta) override;
    
private:
    const int static fontSize = 25;
    constexpr char static *fontpath = "fonts/arial.ttf";
    
    cocos2d::Sprite * JailL = nullptr;
    cocos2d::Label * usernameL = nullptr;
    cocos2d::Label * charNameL = nullptr;
    cocos2d::Label * hpL = nullptr;
    cocos2d::Sprite * SergeantL = nullptr;
    cocos2d::ui::Button * selectB = nullptr;
    
    
    std::string username_ = "username";
    std::string charName_ = "character";
    int hp_ = 0;
    int team_ = -1;
    bool isJail_ = false;
    bool selectVisiable_ = false;
    int position_;
    
};


enum class CardColor{
  BLUE, ORANGE
};

class CardButton : public cocos2d::ui::Button {
public:
    static CardButton * create(const CardColor &color);
    void my_init(const std::string& cardName, int number, int suit);
    bool is_Move() const{
        return isMoved_;
    }
    void set_Move(bool isMove){
        isMoved_ = isMove;
    }
    bool isTouched(){
        return touched_;
    }
    void set_touch(bool touch){
        touched_ = touch;
    }
    int get_cardID(){
        return cardID_;
    }
    const std::string get_cardName() const{
        return cardName_;
    }
    void set_cardID(int id){
        cardID_ = id;
    }
    void set_cardName(const std::string cardName){
        cardName_ = cardName;
    }
    
    void set_DoubleSelect(bool isDS){
        isDoubleSelect_ = isDS;
    }
    
    bool isDoubleSelect() const{
        return isDoubleSelect_;
    }
    
private:
    bool isDoubleSelect_ = false;
    int cardID_ = 0;
    std::string cardName_ = "";
    
    
    bool isMoved_ = false;
    bool touched_ = false;
    const int static fontSize = 30;
    constexpr char static *fontpath = "fonts/arial_Bold.ttf";
    constexpr char static *bluepath = "card-blue.png";
    constexpr char static *blue_dark_path = "card-blue-dark.png";
    constexpr char static *orangepath = "card-orange.png";
    constexpr char static *orange_dark_path = "card-orange-dark.png";
};



//================Game Scene======================
class GameScene : public cocos2d::Scene{
public:
    
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    CREATE_FUNC(GameScene);
    
    
    void update(float delta) override;
    
    static void set_action(int action){
        GameScene::action_ = action;
    }
    
    void myTurnEnded();
    
    
    void CardTouchCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type, int idx);
    void endButtonCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    
    
    CardButton* cardbutton[10] = {};
    int cardbutton_amount = 0;
    
    void set_WinOrLose(WinAndLose worl);
    
    //choose card list
    std::vector<int> chooseList;
    
private:
    
    //static GameScene* myself;
    
    WinAndLose WorL_;

    static int action_;
    
    cocos2d::ui::Button* endButton = nullptr;
    
    MissLayer* popMenu = nullptr;
    
    
    PlayerHead *ShowPlayer[6] = {};
    int myHP_ = 0;
    
};


#endif /* GameScene_hpp */
