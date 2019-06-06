//
//  GameScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/3.
//

#include "GameScene.hpp"
#include "player.hpp"
#include "ClientSocket.hpp"
#include "WrapInfo.hpp"
#include "UseCardHolding.hpp"
#include "ChooseMissPopOut.hpp"
#include "ChooseCardScene.hpp"
#include "Card.hpp"
USING_NS_CC;


float calculate_head_pos(int pos, int n){
    float delta = 1134/n;
    return 100 + pos*delta + 1134/(n*2);
}
float calculate_card_pos(int pos, int n){
    // 257 一張卡
    float edge = (1334 - ((n-1)/1.5)*257 - 257) / 2 + 257/1.5;
    float delta = 257/1.5;
    return edge + pos*delta;
}


Scene *GameScene::createScene(){
    myself = GameScene::create();
    return myself;
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
    
    //turn end button
    endButton = ui::Button::create("login-btn.png");
    endButton->ignoreContentAdaptWithSize(false);
    endButton->setContentSize(Size(200, 75));
    auto endLabel = Label::createWithTTF("End", "fonts/arial.ttf", 40);
    endLabel->setPosition(Vec2(endButton->getContentSize().width/2, endButton->getContentSize().height/2));
    endButton->addChild(endLabel);
    endButton->setPosition(Vec2(visibleSize.width-150, visibleSize.height/2-50));
    endButton->setVisible(false); //Only in my turn visiable
    this->addChild(endButton);
    
    
    auto playerDB = PlayerDatabase::getInstance();
    
    //temp test info============
    /*
    playerDB->set_Mine(5, 5, 1, "tt", "tt", 11);
    
    for(int i=0; i<3; i++){
        playerDB->add_Player(new Player(5, 4, 0, "Username", "Test", i, 0));
    }
     */
    //==========================
    
    
    //show Player Head and information
    
    for(int i=0; i<playerDB->get_size(); i++){
        if(playerDB->get_Player(i)->get_position() != playerDB->get_Mine()->get_position()){
            ShowPlayer[i] = PlayerHead::create();
            ShowPlayer[i]->setPosition(Vec2(calculate_head_pos(i, playerDB->get_size() ) , visibleSize.height-175));
            ShowPlayer[i]->init(playerDB->get_Player(i)->get_PlayerName() , playerDB->get_Player(i)->get_charName(), playerDB->get_Player(i)->get_hp(), playerDB->get_Player(i)->get_team(), playerDB->get_Player(i)->isJail(), playerDB->get_Player(i)->get_position());
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
    if(playerDB->get_Mine()->get_team() == 0){
        SergeantLabel->setVisible(true);
    }
    else{
        SergeantLabel->setVisible(false);
    }
    this->addChild(SergeantLabel);
    
    //===========================================================================================
    
    
    
    
    
   
    this->cardbutton_amount = playerDB->get_Mine()->get_holding_card_amount();
    auto cardVec = playerDB->get_Mine()->get_holding();
    
    
    for(int i=0; i<cardVec.size(); i++){
        
        auto card = CardDatabase::getInstance()->get_Card_byID(cardVec[i]);
        
        cardbutton[i] = CardButton::create(CardColor::BLUE);
        cardbutton[i]->setPosition(Vec2(calculate_card_pos(i, cardVec.size()), 100));
        cardbutton[i]->my_init(card->get_cardName(), card->get_number(), card->get_suit());
        cardbutton[i]->set_cardID(card->get_id());
        
        cardbutton[i]->addTouchEventListener(CC_CALLBACK_2(GameScene::CardTouchCallback, this, i));
        
        this->addChild(cardbutton[i], 0);
        
    }
    
    //choose miss window
    popMenu = MissLayer::create();
    popMenu->setVisible(false);
    this->addChild(popMenu, 200);
    
    //choose card window
    
    auto ChooseLayer = ChooseCardLayer::create();
    this->addChild(ChooseLayer, 200);
    ChooseLayer->setVisible(false);
    ChooseLayer->setTag(2);
    
    this->scheduleUpdate();
    
    return true;
}

//auto updata in every frame
int GameScene::action_ = -1;

void GameScene::update(float /*delta*/) {
    
    
    
    std::cout<<"action : "<<action_<<std::endl;
    switch(action_){
        case 8:{
            //your turn
            endButton->setVisible(true);
            for(int i=0; i<cardbutton_amount; i++){
                cardbutton[i]->setEnabled(true);
            }
            break;
        }
        case 12:{
            //you were bang!
            popMenu->setVisible(true);
            break;
        }
        case 13:{
            //end your turn
            action_ = -1;
            break;
        }
        case -1:{
            popMenu->setVisible(false);
            
            for(int i=0; i<PlayerDatabase::getInstance()->get_size(); i++){
                if(ShowPlayer[i]->get_position() != PlayerDatabase::getInstance()->get_Mine()->get_position()){
                    ShowPlayer[i]->set_selectVisiable(false);
                }
            }
            
            for(int i=0; i<cardbutton_amount; i++){ //card
                cardbutton[i]->setEnabled(false); // set card disable, if not my turn
                
                
                if(cardbutton[i]->isTouched()){
                    if(!cardbutton[i]->is_Move()){  //show card up
                        cardbutton[i]->set_Move(true);
                        cardbutton[i]->setZOrder(100);
                        cardbutton[i]->runAction(MoveBy::create(0.2, Vec2(0, 50)));
                    }
                    else if(cardbutton[i]->isDoubleSelect()){  // use card
                        auto cardHoding = UseCardHolding::getInstance();
                        cardHoding->set_cardID(cardbutton[i]->get_cardID());
                        cardHoding->set_cardName(cardbutton[i]->get_cardName());
                        //std::cout<<"i\n";
                        
                        if(cardHoding->shouldChooseTarget()){ // if use card need to choose target
                            //std::cout<<"shoud choose\n";
                            
                            for(int i=0; i<PlayerDatabase::getInstance()->get_size(); i++){
                                if(ShowPlayer[i]->get_position() != PlayerDatabase::getInstance()->get_Mine()->get_position()){
                                    ShowPlayer[i]->set_selectVisiable(true);
                                }
                            }
                        }
                        //Send Use card Message
                        if(cardHoding->infoFinish()){
                            auto client = CClientSocket::getInstance();
                            client->sendMessage(WrapInfo::WrapUserUseCard(cardHoding->get_cardID(), cardHoding->get_target()));
                            cardHoding->reset(); //reset the CardHolding infomation
                        }
                    }
                    
                }
                else if(!cardbutton[i]->isTouched()){
                    if(cardbutton[i]->is_Move()){
                        cardbutton[i]->set_Move(false);
                        cardbutton[i]->setZOrder(i+1);
                        cardbutton[i]->runAction(MoveBy::create(0.2, Vec2(0, -50)));
                    }
                }
            }
            break;
        }
        default:{
            action_ = -1;
            break;
        }
    }
    
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
void PlayerHead::init(const std::string username, const std::string charName, int hp, int team, bool isJail, int position){
    username_ = username;
    charName_ = charName;
    hp_ = hp;
    team_ = team;
    isJail_ = isJail;
    position_ = position;
    
    usernameL = Label::createWithTTF(username, fontpath, fontSize);
    charNameL = Label::createWithTTF(charName, fontpath, fontSize);
    hpL = Label::createWithTTF("[HP:" + std::to_string(hp) + "]", fontpath, fontSize);
    
    //select button
    selectB = ui::Button::create("brown-dot.png");
    selectB->ignoreContentAdaptWithSize(false);
    selectB->setContentSize(Size(90, 90));
    selectB->setPosition(Vec2(this->getContentSize().width/2, - this->getContentSize().height + 20));
    selectB->setVisible(selectVisiable_);
    selectB->addTouchEventListener(CC_CALLBACK_0(PlayerHead::SelectButtonCallback, this));
    
    this->addChild(selectB);
    
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
    
    this->scheduleUpdate();
}

void PlayerHead::update(float /*delta*/){
    selectB->setVisible(selectVisiable_);
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
void PlayerHead::set_selectVisiable(bool visiable){
    selectVisiable_ = visiable;
}
int PlayerHead::get_position() const{
    return position_;
}

void PlayerHead::SelectButtonCallback(){
    auto uch = UseCardHolding::getInstance();
    uch->set_target(this->get_position());
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
    set_cardName(cardName);
    auto nameL = Label::createWithTTF(cardName_, fontpath, fontSize);
    nameL->setColor(Color3B::BLACK);
    nameL->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height - 50));
    this->addChild(nameL);
}
//=======================GaneScene=======================

void GameScene::CardTouchCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type, int idx){
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:{
            //std::cout<<"touch\n";
            for(int i=0; i<cardbutton_amount; i++){
                if(i!=idx){
                    cardbutton[i]->set_touch(false);
                }
                else{
                    if(cardbutton[i]->isTouched()){
                        cardbutton[i]->set_DoubleSelect(true);
                    }
                    else{
                        cardbutton[i]->set_touch(true);
                    }
                }
            }
            break;
        }
        default:
            break;
            
    }
}

void GameScene::myTurnEnded(){
    auto client = CClientSocket::getInstance();
    client->sendMessage(WrapInfo::WrapUserEndTurn());
    endButton->setVisible(false);
    action_ = -1;
}

GameScene* GameScene::myself = nullptr;

void GameScene::endButtonCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            GameScene::myTurnEnded();
            break;
        }
        default:
            break;
            
    }
}

