//
//  LoungeScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/29.
//

#include "LoungeScene.hpp"
#include "WrapInfo.hpp"
#include <sstream>

//==========================================================================


LoungeUserDatabase * LoungeUserDatabase::myself = nullptr;

//Lounge table scroll view
USING_NS_CC_EXT;
USING_NS_CC;

void LoungeUserTable::tableCellTouched(TableView *table, TableViewCell *cell){
    CCLOG("you touch cell index = %zd", cell->getIdx());
}

CCSize LoungeUserTable::cellSizeForTable(TableView *table){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(300, 64);
}

//number of lounge
ssize_t LoungeUserTable::numberOfCellsInTableView(TableView *table){
    Udatabase = LoungeUserDatabase::getInstance();
    return Udatabase->get_size();
}

TableViewCell* LoungeUserTable::tableCellAtIndex(TableView *table, ssize_t idx){
    //CCLOG("%d", idx);
    
    Udatabase = LoungeUserDatabase::getInstance();
    
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    
    
    //user id label
    unsigned int ID = Udatabase->get_LoungeUserInfo(idx)->getID();
    std::stringstream ss;
    ss<<ID;
    std::string sID = ss.str();
    auto label = Label::createWithTTF(sID, "fonts/arial.ttf", 35);
    label->setPosition(Vec2(20, 9));
    label->setAnchorPoint(Vec2(0, 0));
    label->setColor(Color3B::BLACK);
    cell->addChild(label);
    
    //Lounge user Readyt
    bool UserReady = Udatabase->get_LoungeUserInfo(idx)->isReady();
    
    const std::string sready = "Ready";
    
    auto readyLabel = Label::createWithTTF(sready, "fonts/arial.ttf" , 25);
    readyLabel->setPosition(Vec2(225, 10));
    readyLabel->setAnchorPoint(Vec2(0, 0));
    readyLabel->setColor(Color3B::GREEN);
    cell->addChild(readyLabel);
    
    readyLabel->setVisible(UserReady); // if user ready
    
    
    
    
    
    
    return cell;
    
}

void LoungeUserTable::scrollViewDidScroll(ScrollView *view){}
void LoungeUserTable::scrollViewDidZoom(ScrollView *view){}

bool LoungeUserTable::init(){
    if(!CCLayer::init()){
        return false;
    }
    /*
     auto backGroundColor = CCLayerColor::create(ccc4(255,255,255, 255)); //RGBA
     this->addChild(backGroundColor, 0);
     */
    
    //get lounge list from the server
    std::thread Tmpthread(&LoungeUserTable::getUserListFromServer, this );
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
    auto TopLabel = Label::createWithTTF("User list", "fonts/arial.ttf" , 50);
    TopLabel->setColor(Color3B::BLACK);
    TopLabel->setPosition(Vec2(150, visibleSize.height-130));
    this->addChild(TopLabel);
    
    
    this->schedule(schedule_selector(LoungeUserTable::updateUserInfo), 2.0f ); // update user info 
    
    return true;
    
    
}

// Called every second. The update is scheduled in `init()`.
void LoungeUserTable::updateUserInfo(float /*delta*/){
    if(!LoungeUserDatabase::getInstance()->is_all_user_ready()){
        std::thread Tmpthread(&LoungeUserTable::getUserListFromServer, this );
        Tmpthread.join();
    }
    tableview->reloadData();
}

void LoungeUserTable::getUserListFromServer(){
    
    auto client = Client::getInstance();
    
    Udatabase = LoungeUserDatabase::getInstance();
    
    CClientSocket::getInstance()->sendMessage(WrapInfo::WrapLoungeUserInfo().dump());
    
}


