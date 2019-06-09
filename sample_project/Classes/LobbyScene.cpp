//
//  LobbyScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/22.
//

#include "LobbyScene.hpp"
#include "SettingScene.hpp"
#include "RankScene.hpp"
#include "FriendScene.hpp"
#include "AssisstanceFunc.hpp"
#include "LoungeScene.hpp"
#include "ChooseCharacterScene.hpp"

#include <sstream>

#include <thread>
#include <nlohmann/json.hpp>

#include "User.hpp"
#include "player.hpp"
#include "Card.hpp"
#include "NetworkCom.hpp"

USING_NS_CC;

void initRoomInfo(const json& rec);

// The images for the buttons.
static const std::string kNormalButtonImage = "notification-btn.png";
static const std::string kSelectedButtonImage = "notification-btn-click.png";
static const std::string kDisabledButtonImage = "notification-btn.png";

/// Padding for the UI elements.
static const float kUIElementPadding = -20;

/// The title text size for the Firebase buttons.
static const float kButtonTitleFontSize = 45.0;

/// The content size for the Firebase buttons.
static const cocos2d::Size kButtonContentSize = cocos2d::Size(300, 100);




// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

bool LobbyScene::intoLounge_ = false;

LobbyScene* LobbyScene::myself = nullptr;

Scene *LobbyScene::createScene(){
    myself = LobbyScene::create();
    return myself;
}


void LobbyScene::ListenerStartGame(){
    CClientSocket::getInstance()->busyWaitting(6);
    std::cout<<"REC ACTION 6\n";
    isStartGame_ = true;
}

// on "init" you need to initialize your instance
bool LobbyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    std::thread tThread(&LobbyScene::ListenerStartGame, this);
    tThread.detach();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //add backbround
    auto backGroundColor = CCLayerColor::create(ccc4(236, 207, 177, 255)); //RGBA
    this->addChild(backGroundColor, 0);
    
    //==============================================================================================================
    //Button X pos
    const float  ButtonXPosition = origin.x + visibleSize.width - 100;
    
    //Rank button
    auto RankButton = createButton(true, "Rank", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    nextYPosition = origin.y + visibleSize.height * 2 / 3;
    RankButton->setPosition(Vec2(ButtonXPosition, nextYPosition));
    RankButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::RankCallback, this));
    RankButton->setPosition(Vec2(visibleSize.width/4-165, visibleSize.height/4+ 50 ));
    RankButton->setTag(0);
    this->addChild(RankButton);
    
    //Store button
    auto StoreButton = createButton(true, "Store", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    StoreButton->setPosition(Vec2(visibleSize.width/4 + 165 , visibleSize.height/4 + 50 ));
    StoreButton->setTag(1);
    this->addChild(StoreButton);
    
    //Friend button
    auto FriendButton = createButton(true, "Friend", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    FriendButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::FriendCallback, this));
    FriendButton->setPosition(Vec2(visibleSize.width/4- 165  , visibleSize.height/4-50 ));
    FriendButton->setTag(2);
    this->addChild(FriendButton);
    
    //Setting button
    auto SettingButton = createButton(true, "Setting", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    SettingButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::SettingCallback, this));
    SettingButton->setPosition(Vec2(visibleSize.width/4 + 165 , visibleSize.height/4 - 50 ));
    SettingButton->setTag(3);
    this->addChild(SettingButton);
    
    //raady button
    auto Readybutton  = cocos2d::ui::Button::create("ready-btn.png", "ready-btn-click.png", "ready-btn.png"); //2329 x 636
    Readybutton->setPosition(Vec2(visibleSize.width/4, visibleSize.height/4));
    Readybutton->ignoreContentAdaptWithSize(false);
    Readybutton->setContentSize(Size(2329/4, 636/4));
    Readybutton->setVisible(intoLounge_);
    Readybutton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::ReadyCallback, this));
    Readybutton->setTag(5);
    this->addChild(Readybutton);
    
    //game button
    auto Gamebutton  = cocos2d::ui::Button::create("game-btn.png", "game-btn-click.png", "game-btn.png"); //2329 x 636
    Gamebutton->setPosition(Vec2(visibleSize.width/4, visibleSize.height/4));
    Gamebutton->ignoreContentAdaptWithSize(false);
    Gamebutton->setContentSize(Size(2329/4, 636/4));
    Gamebutton->setVisible(false);
    Gamebutton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::GameCallback, this));
    Gamebutton->setTag(7);
    this->addChild(Gamebutton);
    
    //==============================================================================================================
    
    //======================================
    //get User information from server
    
    std::thread mythread(&LobbyScene::getInfoFromServer, this);
    mythread.join();
    
    
    //======================================
    
    //Username Label
    showName_ = User::getInstance()->getNickName();
    
    auto UsernameLabel = Label::createWithTTF(showName_, "fonts/arial.ttf", 40);
    UsernameLabel->setAnchorPoint(Vec2(0,1)); //以左上角為緢點
    UsernameLabel->setColor(Color3B::BLACK);
    UsernameLabel->setPosition(Vec2(origin.x + 20, origin.y + visibleSize.height - 20));
    
    this->addChild(UsernameLabel);
    

    //Hash uid Label
    unsigned int IntUID = User::getInstance()->getUID();
    std::stringstream sUID;
    sUID << IntUID; // int to string
    auto IntUIDLabel = Label::createWithTTF(sUID.str(), "fonts/arial.ttf", 30);
    IntUIDLabel->setAnchorPoint(Vec2(0,1)); //以左上角為緢點
    IntUIDLabel->setColor(Color3B::BLACK);
    IntUIDLabel->setPosition(Vec2(origin.x + 20, UsernameLabel->getPosition().y - 50));
    
    CCUserDefault::sharedUserDefault()->setStringForKey("UID", sUID.str());
    
    this->addChild(IntUIDLabel);

    //User W/L information
    showWin_ = User::getInstance()->getWin(), showLose_ = User::getInstance()->getLose();
    //win = CCUserDefault::sharedUserDefault()->getIntegerForKey("win");
    //lose = CCUserDefault::sharedUserDefault()->getIntegerForKey("lose");
    
    auto MyScore = Label::createWithTTF("My Score:", "fonts/arial_Bold.ttf", 100);
    MyScore->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y+visibleSize.height*2/3));
    MyScore->setColor(Color3B::BLACK);
    std::string WinAndLoss = std::to_string(showWin_) + "W" + " " +std::to_string(showLose_) + "L";
    
    auto Score = Label::createWithTTF(WinAndLoss, "fonts/arial_Bold.ttf", 100);
    Score->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y+visibleSize.height*2/3 - MyScore->getContentSize().height ));
    Score->setColor(Color3B::BLACK);
    this->addChild(MyScore);
    this->addChild(Score);
    
    
    
    //Lounge list table
    auto lounge_table = LoungeTable::create();
    lounge_table->setContentSize(Size(1337/4, 750));
    lounge_table->ignoreAnchorPointForPosition(false);
    lounge_table->setAnchorPoint(Vec2(0.5, 1));
    lounge_table->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height));
    lounge_table->setTag(4);
    this->addChild(lounge_table, 1);
    
    
    //Lounge User list table
    auto user_table = LoungeUserTable::create();
    user_table->setContentSize(Size(1337/4, 750));
    user_table->ignoreAnchorPointForPosition(false);
    user_table->setAnchorPoint(Vec2(0.5, 1));
    user_table->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height));
    user_table->setTag(6);
    this->addChild(user_table, 1);
    
    
    //lounge list background
    auto friend_bg = Sprite::create("friend-bg.png");
    friend_bg->setContentSize(Size(visibleSize.width/4 + 100, 600));
    friend_bg->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height/2));
    this->addChild(friend_bg, 0);
    
    
    // Schedule the update method for this scene.
    this->scheduleUpdate();
    return true;
    
    
    
    
}

// Called automatically every frame. The update is scheduled in `init()`.
void LobbyScene::update(float /*delta*/){
    //update show info
    showWin_ = User::getInstance()->getWin(), showLose_ = User::getInstance()->getLose();
    showName_ = User::getInstance()->getNickName();
    
    if(isStartGame_){
        auto scene = ChooseCharacterScene::createScene();
        Director::getInstance()->replaceScene(scene);
    }
    for(int i=0; i<=4; i++){
        auto sp = this->getChildByTag(i);
        sp->setVisible(!intoLounge_);
    }
    for(int i=5; i<=6; i++){
        auto sp = this->getChildByTag(i);
        sp->setVisible(intoLounge_);
    }
    
    if(LoungeUserDatabase::getInstance()->is_all_user_ready()){
        
        
        if(User::getInstance()->getWhereLounge() == User::getInstance()->getUID()){
            auto sp = this->getChildByTag(5);//ready button
            sp->setVisible(false);
            
            sp = this->getChildByTag(7);//game button
            sp->setVisible(true);
            
        }
        
    }
}


cocos2d::ui::Button* LobbyScene::createButton(
                                                 bool buttonEnabled, const std::string& buttonTitleText,
                                                 const cocos2d::Color3B& buttonColor, const std::string& ImagePath1, const std::string& ImagePath2, const std::string& ImagePath3) {
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    cocos2d::ui::Button* button = cocos2d::ui::Button::create(
                                                              ImagePath1, ImagePath2, ImagePath3);
    
    const float  ButtonXPosition = origin.x + visibleSize.width - 100;
    
    button->setEnabled(buttonEnabled);
    button->setTitleColor(buttonColor);
    button->setTitleText(buttonTitleText);
    button->setTitleFontSize(kButtonTitleFontSize);
    button->ignoreContentAdaptWithSize(false);
    button->setContentSize(kButtonContentSize);
    nextYPosition -= button->getContentSize().height + kUIElementPadding;
    button->setPosition(cocos2d::Vec2(ButtonXPosition, nextYPosition));
    button->setTitleOffset(0, 0);
    
    return button;
}
//Select Setting button call back
void LobbyScene::SettingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            auto scene = SettingScene::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
            break;
        }
        
        default:
            break;
       
    }
}
//Select Rank button call back
void LobbyScene::RankCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            auto scene = RankScene::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
            break;
        }
            
        default:
            break;
            
    }
}
//Select Friend button call back
void LobbyScene::FriendCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            auto scene = FriendScene::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
            break;
        }
            
        default:
            break;
            
    }
}

//Select Ready button call back
void LobbyScene::ReadyCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            std::thread tThread([](){
                auto client = Client::getInstance();
                auto user = User::getInstance();
                
                
                CClientSocket::getInstance()->sendMessage(WrapInfo::WrapSetReady(!user->isReady()).dump());
                user->setReady(! (user->isReady()) );
            });
            tThread.join();
            break;
        }
        default:
            break;
            
    }
}


//Select Game button call back
void LobbyScene::GameCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            std::thread tThread([&](){
                auto client = Client::getInstance();
                CClientSocket::getInstance()->sendMessage(WrapInfo::WrapStartGame().dump());
                CClientSocket::getInstance()->busyWaitting(6);
                isStartGame_ = true;
            });
            tThread.join();
            /*
            auto dir = Director::getInstance();
            auto scene = ChooseCharacterScene::create();
            dir->replaceScene(scene);
             */
            
            break;
        }
        default:
            break;
            
    }
}



//==========================================================================

LoungeDatabase * LoungeDatabase::myself = nullptr;
//Lounge table scroll view
USING_NS_CC_EXT;

void LoungeTable::tableCellTouched(TableView *table, TableViewCell *cell){
    int idx = cell->getIdx();
    CCLOG("you touch cell index = %zd", idx);
    
    std::thread joinThread(LobbyScene::joinLounge, Ldatabase->get_LoungeInfo(idx)->getID());
    joinThread.join();
    
}

CCSize LoungeTable::cellSizeForTable(TableView *table){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(300, 64);
}

//number of lounge
ssize_t LoungeTable::numberOfCellsInTableView(TableView *table){
    Ldatabase = LoungeDatabase::getInstance();
    return Ldatabase->get_size();
}

TableViewCell* LoungeTable::tableCellAtIndex(TableView *table, ssize_t idx){
    //CCLOG("%d", idx);
    Ldatabase = LoungeDatabase::getInstance();
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    
    //BK image
    auto btImage = Sprite::create("lobby-room-btn.png");
    btImage->setContentSize(Size(300, 80));
    btImage->setPosition(Vec2(150, 32));
    cell->addChild(btImage);
    
    //user id label
    unsigned int ID = Ldatabase->get_LoungeInfo(idx)->getID();
    std::stringstream ss;
    ss<<ID;
    std::string sID = ss.str();
    auto label = Label::createWithTTF(sID, "fonts/arial.ttf", 35);
    label->setPosition(Vec2(25, 9));
    label->setAnchorPoint(Vec2(0, 0));
    label->setColor(Color3B::BLACK);
    cell->addChild(label);
    
    //Lounge user amount
    int userAmount = Ldatabase->get_LoungeInfo(idx)->getAmount();
    std::stringstream ss2;
    ss2<<userAmount;
    std::string sAmount = ss2.str();
    
    auto amountLabel = Label::createWithTTF(sAmount + " p", "fonts/arial.ttf" , 25);
    amountLabel->setPosition(Vec2(240, 10));
    amountLabel->setAnchorPoint(Vec2(0, 0));
    amountLabel->setColor(Color3B::BLACK);
    cell->addChild(amountLabel);
    
    
    
    
    
    return cell;
    
}

void LoungeTable::scrollViewDidScroll(ScrollView *view){}
void LoungeTable::scrollViewDidZoom(ScrollView *view){}

bool LoungeTable::init(){
    if(!CCLayer::init()){
        return false;
    }
    Ldatabase = LoungeDatabase::getInstance();
    /*
     auto backGroundColor = CCLayerColor::create(ccc4(255,255,255, 255)); //RGBA
     this->addChild(backGroundColor, 0);
     */
    
    //get lounge list from the server
    std::thread Tmpthread(&LoungeTable::getLoungListFromServer, this );
    Tmpthread.join();
    
    
    
    auto visibleSize =  this->getContentSize();
    
    
    //Lounge list
    tableview = TableView::create(this, CCSizeMake(300, 480)); //table size
    tableview->setDirection(ScrollView::Direction::VERTICAL); // 只能垂直滑動
    tableview->setDelegate(this);
    tableview->ignoreAnchorPointForPosition(false);
    tableview->setAnchorPoint(Vec2(0, 1));
    tableview->setPosition(Vec2(0, visibleSize.height-170));
    this->addChild(tableview);
    tableview->reloadData();
    
    //friend list label
    auto TopLabel = Label::createWithTTF("Lobby list", "fonts/arial.ttf" , 50);
    TopLabel->setColor(Color3B::BLACK);
    TopLabel->setPosition(Vec2(150, visibleSize.height-130));
    this->addChild(TopLabel);
    
    this->schedule(schedule_selector(LoungeTable::updateUserInfo), 2.0f ); // update user info
    
    return true;
    
    
}
void LoungeTable::updateUserInfo(float /*delta*/){
    if(! LobbyScene::getInstance()->isIntoLounge()){
        std::thread Tmpthread(&::LoungeTable::getLoungListFromServer, this );
        Tmpthread.join();
    }
    tableview->reloadData();
}


void LoungeTable::getLoungListFromServer(){
    
    CClientSocket::getInstance()->sendMessage(WrapInfo::WrapGetLoungeListInfo().dump());
}


void LobbyScene::joinLounge(unsigned int lounge_id){
    auto client = Client::getInstance();
    auto user = User::getInstance();
    user->setWhereLounge(lounge_id);
    CClientSocket::getInstance()->sendMessage(WrapInfo::WrapJoinLounge(true, lounge_id, 0).dump());
    CClientSocket::getInstance()->busyWaitting(3);
    intoLounge_ = true;
}


