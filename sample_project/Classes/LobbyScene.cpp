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
#include <sstream>

#include <thread>
#include <nlohmann/json.hpp>

#include "User.hpp"
#include "NetworkCom.hpp"

USING_NS_CC;

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

Scene *LobbyScene::createScene(){
    return LobbyScene::create();
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
    
    this->addChild(RankButton);
    //Store button
    auto StoreButton = createButton(true, "Store", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    StoreButton->setPosition(Vec2(visibleSize.width/4 + 165 , visibleSize.height/4 + 50 ));
    this->addChild(StoreButton);
    
    //Friend button
    auto FriendButton = createButton(true, "Friend", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    FriendButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::FriendCallback, this));
    FriendButton->setPosition(Vec2(visibleSize.width/4- 165  , visibleSize.height/4-50 ));
    this->addChild(FriendButton);
    
    //Setting button
    auto SettingButton = createButton(true, "Setting", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    SettingButton->addTouchEventListener(CC_CALLBACK_2(LobbyScene::SettingCallback, this));
    SettingButton->setPosition(Vec2(visibleSize.width/4 + 165 , visibleSize.height/4 - 50 ));
    this->addChild(SettingButton);
    //==============================================================================================================
    
    //======================================
    //get User information from server
    
    std::thread mythread(&LobbyScene::getInfoFromServer, this);
    mythread.join();
    
    //======================================
    
    //Username Label
    const std::string Username = User::getInstance()->getNickName();
    
    auto UsernameLabel = Label::createWithTTF(Username, "fonts/arial.ttf", 40);
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
    int win = User::getInstance()->getWin(), lose = User::getInstance()->getLose();
    //win = CCUserDefault::sharedUserDefault()->getIntegerForKey("win");
    //lose = CCUserDefault::sharedUserDefault()->getIntegerForKey("lose");
    
    auto MyScore = Label::createWithTTF("My Score:", "fonts/arial_Bold.ttf", 100);
    MyScore->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y+visibleSize.height*2/3));
    MyScore->setColor(Color3B::BLACK);
    std::string WinAndLoss = std::to_string(win) + "W" + " " +std::to_string(lose) + "L";
    
    auto Score = Label::createWithTTF(WinAndLoss, "fonts/arial_Bold.ttf", 100);
    Score->setPosition(Vec2(origin.x + visibleSize.width/4, origin.y+visibleSize.height*2/3 - MyScore->getContentSize().height ));
    Score->setColor(Color3B::BLACK);
    this->addChild(MyScore);
    this->addChild(Score);
    
    /*
    //start Game button
    const std::string gameButtonPath = "startgame-btn.png"; ////3245 × 591
    const std::string gameButtonSelectedPath = "startgame-btn-click.png"; ////3245 × 591
    auto gameButton = createButton(true, "Game", Color3B::BLACK, gameButtonPath, gameButtonSelectedPath, gameButtonPath);
    gameButton->setContentSize(Size(3245/4, 591/4));
    gameButton->setTitleFontSize(85);
    gameButton->setAnchorPoint(Vec2(0, 0.5));
    gameButton->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height/4));
    gameButton->setTitleOffset(0, 0);
    this->addChild(gameButton);
    */
    
    //Lounge list table
    auto lounge_table = LoungeTable::create();
    lounge_table->setContentSize(Size(1337/4, 750));
    lounge_table->ignoreAnchorPointForPosition(false);
    lounge_table->setAnchorPoint(Vec2(0.5, 1));
    lounge_table->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height));
    this->addChild(lounge_table, 1);
    
    //lounge list background
    auto friend_bg = Sprite::create("friend-bg.png");
    friend_bg->setContentSize(Size(visibleSize.width/4 + 100, 600));
    friend_bg->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height/2));
    this->addChild(friend_bg);
    
    return true;
    
    
    
    
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





//==========================================================================

LoungeDatabase * LoungeDatabase::myself = nullptr;
//Lounge table scroll view
USING_NS_CC_EXT;

void LoungeTable::tableCellTouched(TableView *table, TableViewCell *cell){
    CCLOG("you touch cell index = %zd", cell->getIdx());
}

CCSize LoungeTable::cellSizeForTable(TableView *table){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(300, 64);
}

//number of lounge
ssize_t LoungeTable::numberOfCellsInTableView(TableView *table){
    Ldatabase = LoungeDatabase::getInstance();
    return Ldatabase->get_size() - 1;
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
    /*
     auto backGroundColor = CCLayerColor::create(ccc4(255,255,255, 255)); //RGBA
     this->addChild(backGroundColor, 0);
     */
    
    //get lounge list from the server
    std::thread Tmpthread(&LoungeTable::getLoungListFromServer, this );
    Tmpthread.join();
    
    
    
    auto visibleSize =  this->getContentSize();
    
    
    //Lounge list
    TableView * tableview = TableView::create(this, CCSizeMake(300, 480)); //table size
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
    return true;
    
    
}

void LoungeTable::getLoungListFromServer(){
    auto client = Client::getInstance();
    
    Ldatabase = LoungeDatabase::getInstance();
    
    json rec = client->getLoungeinfo();
    int loungSize = rec["Lounge Amount"];
    Ldatabase->set_size(loungSize);
    
    CCLOG(rec.dump().c_str());
    //Lounge 0, Loung 1 ....
    
    std::string sLounge = "Lounge ";
    
    for(int i=0;  i<loungSize; i++){
        stringstream ss;
        ss<<i;
        sLounge += ss.str();
        
        unsigned int tID = rec[sLounge]["ID"];
        int tAmount = rec[sLounge]["User Amount"];
        
        Ldatabase->add_Lounge(new LoungeInfo(tID, tAmount));
    }
    
}
