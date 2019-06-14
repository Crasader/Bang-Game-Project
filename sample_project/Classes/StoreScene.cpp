//
//  StoreScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/12.
//

#include "StoreScene.hpp"

#include "LobbyScene.hpp"
#include "WrapInfo.hpp"

USING_NS_CC;



const std::string backButtonImage = "back-icon.png"; //square
const std::string backButtonSelectedImage = "back-icon-click.png";//square

Scene *StoreScene::createScene(){
    return StoreScene::create();
}

// on "init" you need to initialize your instance
bool StoreScene::init()
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
    
    //Back button
    auto BackButton = ui::Button::create(backButtonImage, backButtonSelectedImage, backButtonImage);
    BackButton->ignoreContentAdaptWithSize(false);
    BackButton->setContentSize(Size(100, 100));
    BackButton->setPosition(Vec2(origin.x + BackButton->getContentSize().width/2, origin.y + visibleSize.height - BackButton->getContentSize().height/2 ));
    BackButton->addTouchEventListener(CC_CALLBACK_2(StoreScene::BackToLoooby, this));
    this->addChild(BackButton);
    
    //Store Label
    auto storeL = Label::createWithTTF("Store", "fonts/arial.ttf", 70);
    storeL->setColor(Color3B::BLACK);
    storeL->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height*5/7));
    this->addChild(storeL);
    
    
    
    
    
    //==============================================================================================================
  
    
    
    //Friend list table
    auto store_table = StoreTable::create();
    store_table->setContentSize(Size(1337/4, 750));
    store_table->ignoreAnchorPointForPosition(false);
    store_table->setAnchorPoint(Vec2(0.5, 1));
    store_table->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height));
    this->addChild(store_table, 1);
    
    //add table background
    auto friend_bg = Sprite::create("friend-bg.png");
    friend_bg->setContentSize(Size(visibleSize.width/4 + 100, 600));
    friend_bg->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height/2));
    this->addChild(friend_bg, 0);
    
    
    
    return true;
}


void StoreScene::BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            
            auto scene = LobbyScene::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
            break;
        }
            
        default:
            break;
    }
}

void StoreScene::set_description_L(const std::string str, int cost){
    this->removeChild(desL_);
    
    desL_ = Label::createWithTTF(str, "fonts/arial.ttf", 40);
    desL_->setColor(Color3B::BLACK);
    desL_->setDimensions(500, 700);
    desL_->setPosition(Vec2(450, 50));
    desL_->setVisible(true);
    this->addChild(desL_);
    
    this->removeChild(costL_);
    costL_ = Label::createWithTTF("$ : " + to_string(cost), "fonts/arial.ttf", 40);
    costL_->setColor(Color3B::BLACK);
    costL_->setPosition(Vec2(500, desL_->getPosition().y+100));
    costL_->setVisible(true);
    this->addChild(costL_);
    
}
//==========================================================================
//store table scroll view
USING_NS_CC_EXT;

void StoreTable::tableCellTouched(TableView *table, TableViewCell *cell){
    auto runS = static_cast<StoreScene*>(Director::getInstance()->getRunningScene());
    
    int cost = Sdatabase->get_CardInfo(cell->getIdx())->get_Cost();
    runS->set_description_L(Sdatabase->get_CardInfo(cell->getIdx())->get_Description(), cost);
    //card cost
    
    
    
    CCLOG("you touch cell index = %zd", cell->getIdx());
}

CCSize StoreTable::cellSizeForTable(TableView *table){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(300, 64);
}

//number of item
ssize_t StoreTable::numberOfCellsInTableView(TableView *table){
    auto database = StoreDatabase::getInstance();
    return database->Size();
}

TableViewCell* StoreTable::tableCellAtIndex(TableView *table, ssize_t idx){
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    
    
    
    //Card name label
    const std::string Name = Sdatabase->get_CardInfo(static_cast<int>(idx))->get_Name();
    auto label = Label::createWithTTF(Name, "fonts/arial.ttf", 40);
    label->setPosition(Vec2(25, 0));
    label->setAnchorPoint(Vec2(0, 0));
    label->setColor(Color3B::BLACK);
    cell->addChild(label, 1);
    
    
    
    return cell;
    
}

void StoreTable::scrollViewDidScroll(ScrollView *view){}
void StoreTable::scrollViewDidZoom(ScrollView *view){}

bool StoreTable::init(){
    if(!CCLayer::init()){
        return false;
    }

    std::thread Tmpthread(&StoreTable::getStoreFromServer, this);
    Tmpthread.join();
    
    auto visibleSize =  this->getContentSize();
    
    
    //store item list
    TableView * tableview = TableView::create(this, CCSizeMake(300, 480)); //table size
    tableview->setDirection(ScrollView::Direction::VERTICAL); // 只能垂直滑動
    tableview->setDelegate(this);
    tableview->ignoreAnchorPointForPosition(false);
    tableview->setAnchorPoint(Vec2(0, 1));
    tableview->setPosition(Vec2(0, visibleSize.height-170));
    this->addChild(tableview);
    tableview->reloadData();
    
    //Item list label
    auto TopLabel = Label::createWithTTF("Item List", "fonts/arial.ttf" , 50);
    TopLabel->setColor(Color3B::BLACK);
    TopLabel->setPosition(Vec2(150, visibleSize.height-130));
    this->addChild(TopLabel);
    return true;
    
    
}

void StoreTable::getStoreFromServer(){
    Sdatabase = StoreDatabase::getInstance();
    auto client = Client::getInstance();
    CClientSocket::getInstance()->sendMessage(WrapInfo::WrapGetStoreInfo().dump());
    CClientSocket::getInstance()->busyWaitting(25);
}


//Store database
StoreDatabase* StoreDatabase::myself = nullptr;

