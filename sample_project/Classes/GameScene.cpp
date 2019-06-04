//
//  GameScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/3.
//

#include "GameScene.hpp"
#include "player.hpp"


USING_NS_CC;


float calculate_head_pos(int pos, int n){
    float delta = 1134/n;
    return 100 + pos*delta + 1134/(n*2);
}
float calculate_card_pos(int pos, int n){
    // 257 一張卡
    float edge = (1334 - ((n-1)/2)*257 - 257) / 2 + 257/2;
    float delta = 257/2;
    return edge + pos*delta;
}


Scene *GameScene::createScene(){
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //add backbround
    auto backGroundColor = CCLayerColor::create(ccc4(236, 207, 177, 255)); //RGBA
    this->addChild(backGroundColor, 0);
    
    //==============================================================================================================
    
    //temp test info============
    auto playerDB = PlayerDatabase::getInstance();
    
    playerDB->set_Mine(5, 5, 1, "tt", "tt", 11);
    
    for(int i=0; i<3; i++){
        playerDB->add_Player(new Player(5, 4, 0, "Username", "Test", i, 0));
    }
    //==========================
    
    
    //show Player Head and information
    
    for(int i=0; i<playerDB->get_size(); i++){
        if(playerDB->get_Player(i)->get_position() != playerDB->get_Mine()->get_position()){
            ShowPlayer[i] = PlayerHead::create();
            ShowPlayer[i]->setPosition(Vec2(calculate_head_pos(i, playerDB->get_size() ) , visibleSize.height-175));
            ShowPlayer[i]->init(playerDB->get_Player(i)->get_PlayerName() , playerDB->get_Player(i)->get_charName(), playerDB->get_Player(i)->get_hp(), playerDB->get_Player(i)->get_team(), playerDB->get_Player(i)->isJail());
            this->addChild(ShowPlayer[i]);
        }
    }
    
    // show my blood
    myHP_ = playerDB->get_Mine()->get_hp();
    Sprite* mpSprite[6] = {};
    for(int i=0; i<myHP_; i++){
        mpSprite[i] = Sprite::create("hp-logo.png"); // 174 x 253
        mpSprite[i]->setContentSize(Size(174/4, 253/4));
        // not finish 6/3
        
        mpSprite[i]->setPosition(Vec2(visibleSize.width - 50 - (i*40), visibleSize.height - 40));
        this->addChild(mpSprite[i]);
    }
    
    //show my character name
    auto charNameLabel = Label::createWithTTF("character " + playerDB->get_Mine()->get_charName(), "fonts/arial.ttf", 40);
    charNameLabel->setColor(Color3B::BLACK);
    charNameLabel->setAnchorPoint(Vec2(0, 0.5));
    charNameLabel->setPosition(Vec2(30, visibleSize.height- 40));
    this->addChild(charNameLabel);
    
    //show if I am 警長
    auto SergeantLabel = Sprite::create("cap-logo.png"); // 227 x 258
    SergeantLabel->setContentSize(Size(227/4, 258/4));
    SergeantLabel->setPosition(Vec2(charNameLabel->getPosition().x + charNameLabel->getContentSize().width + 50, charNameLabel->getPosition().y));
    if(playerDB->get_Mine()->get_team() == 1){
        SergeantLabel->setVisible(true);
    }
    else{
        SergeantLabel->setVisible(false);
    }
    this->addChild(SergeantLabel);
    
    //===========================================================================================
    
    // Card partion
    CardButton *card[10];
    for(int i=0; i<3; i++){
        card[i] = CardButton::create(CardColor::BLUE);
        card[i]->setPosition(Vec2(calculate_card_pos(i, 3), 100));
        card[i]->my_init("BANG!", 1, 1);
        this->addChild(card[i]);
    }
    
    
    return true;
}










//==============PlayerHead class=====================
/*
PlayerHead::PlayerHead(const std::string username, const std::string charName, int hp, int team):username_(username), charName_(charName), hp_(hp), team_(team){
    
};
PlayerHead::PlayerHead(){};
*/

PlayerHead* PlayerHead::create()
{
    PlayerHead *sprite = new PlayerHead();
    if (sprite && sprite->initWithFile("user-icon.png"))
    {
        sprite->autorelease();
        //sprite->ignoreAnchorPointForPosition(false);
        sprite->setContentSize(Size(579/4, 642/4)); //579 x 642
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void PlayerHead::updataInfo(const std::string username, const std::string charName, int hp, int team, bool isJail){
    
    username_ = username;
    charName_ = charName;
    hp_ = hp;
    team_ = team;
    isJail_ = isJail;
    
    this->removeChild(usernameL, true);
    this->removeChild(charNameL, true);
    this->removeChild(hpL, true);
    
    
    usernameL = Label::createWithTTF(username, fontpath, fontSize);
    charNameL = Label::createWithTTF(charName, fontpath, fontSize);
    hpL = Label::createWithTTF("[HP:" + std::to_string(hp) + "]", fontpath, fontSize);
    
    JailL->setVisible(isJail);
    
    
    usernameL->setColor(Color3B::BLACK);
    charNameL->setColor(Color3B::BLACK);
    hpL->setColor(Color3B::BLACK);
    
    this->addChild(usernameL);
    this->addChild(charNameL);
    this->addChild(hpL);
    
    usernameL->setPosition(Vec2(this->getContentSize().width/2 , -10));
    charNameL->setPosition(Vec2(this->getContentSize().width/2 ,-40));
    hpL->setPosition(Vec2(this->getContentSize().width/2, -70));
    

}
void PlayerHead::init(const std::string username, const std::string charName, int hp, int team, bool isJail){
    username_ = username;
    charName_ = charName;
    hp_ = hp;
    team_ = team;
    isJail_ = isJail;
    
    
    usernameL = Label::createWithTTF(username, fontpath, fontSize);
    charNameL = Label::createWithTTF(charName, fontpath, fontSize);
    hpL = Label::createWithTTF("[HP:" + std::to_string(hp) + "]", fontpath, fontSize);
    
    //Jail logo
    JailL = Sprite::create("card-blue-icon.png");//602 x 224
    JailL->setContentSize(Size(602/5, 224/5));
    auto jLabel = Label::createWithTTF("JAIL", fontpath, fontSize);
    jLabel->setColor(Color3B::BLACK);
    jLabel->setAnchorPoint(Vec2(0.5, 0.5));
    jLabel->setPosition(Vec2(602/10, 224/10));
    JailL->addChild(jLabel);
    JailL->setVisible(isJail);
    
    // Sergent logo
    SergeantL = Sprite::create("cap-logo.png");
    SergeantL->setContentSize(Size(227/4, 258/4));
    SergeantL->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2 - 33));
    if(team_ == 1){
        SergeantL->setVisible(true);
    }
    else{
        SergeantL->setVisible(false);
    }
    this->addChild(SergeantL);
    
    usernameL->setColor(Color3B::BLACK);
    charNameL->setColor(Color3B::BLACK);
    hpL->setColor(Color3B::BLACK);
    
    this->addChild(usernameL);
    this->addChild(charNameL);
    this->addChild(hpL);
    this->addChild(JailL);
    
    usernameL->setPosition(Vec2(this->getContentSize().width/2 , -10));
    charNameL->setPosition(Vec2(this->getContentSize().width/2 ,-40));
    hpL->setPosition(Vec2(this->getContentSize().width/2, -70));
    JailL->setPosition(Vec2(this->getContentSize().width/2, -100));
}




int PlayerHead::get_hp() const{
    return hp_;
}
int PlayerHead::get_team() const{
    return team_;
}
bool PlayerHead::is_Jail() const{
    return isJail_;
}

void PlayerHead::set_username(const std::string username){
    username_ = username;
}
void PlayerHead::set_charName(const std::string charName){
    charName_ = charName;
}
void PlayerHead::set_hp(int hp){
    hp_ = hp;
}
void PlayerHead::set_team(int team){
    team_ = team;
}
void PlayerHead::set_Jail(bool isJail){
    isJail_ = isJail;
}

//==============CardButton class=====================
/*
 PlayerHead::PlayerHead(const std::string username, const std::string charName, int hp, int team):username_(username), charName_(charName), hp_(hp), team_(team){
 
 };
 PlayerHead::PlayerHead(){};
 */


CardButton* CardButton::create(const CardColor &color){
    CardButton *button = new CardButton();
    if (button)
    {
        if(color == CardColor::BLUE){
            if(button->init(bluepath, bluepath, blue_dark_path)){
                button->autorelease();
                button->ignoreContentAdaptWithSize(false);
                button->setContentSize(Size(1154/4.5, 1644/4.5)); //1152 x 1644
                return button;
            }
        }
        else if(color == CardColor::ORANGE){
            if(button->init(orangepath, orangepath, orange_dark_path)){
                button->autorelease();
                button->ignoreContentAdaptWithSize(false);
                button->setContentSize(Size(1154/4.5, 1644/4.5)); //1152 x 1644
                return button;
            }
        }
        
        
    }
    CC_SAFE_DELETE(button);
    return nullptr;
}

void CardButton::my_init(const std::string &cardName, int number, int suit){
    auto nameL = Label::createWithTTF(cardName, fontpath, fontSize);
    nameL->setColor(Color3B::BLACK);
    nameL->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height - 50));
    this->addChild(nameL);
}

