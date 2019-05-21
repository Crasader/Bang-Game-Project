//
//  FriendScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/18.
//

#include "FriendScene.hpp"
#include "LobbyScene.hpp"

USING_NS_CC;




// The images for the buttons.
static const std::string AddButtonImage = "add-btn.png";
static const std::string AddButtonSelectedImage = "add-btn-click.png";

const std::string backButtonImage = "back-icon.png"; //square
const std::string backButtonSelectedImage = "back-icon-click.png";//square
const std::string FriendImage = "friend-logo.png"; //943 x 320
const std::string UsernameInputImage = "username-input.png";





/// The content size for the Firebase buttons.
static const cocos2d::Size InputFieldSize = cocos2d::Size(2025/4, 389/4);





// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

Scene *FriendScene::createScene(){
    return FriendScene::create();
}

// on "init" you need to initialize your instance
bool FriendScene::init()
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
    
    //Friend Label
    
    auto FriendLogo = Sprite::create(FriendImage);
    FriendLogo->setContentSize(Size(943/4, 320/4));
    FriendLogo->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height*5/7));
    this->addChild(FriendLogo);
    
    //==============================================================================================================
    //Button X pos  (middle of window)
    const float  ButtonXPosition = origin.x + visibleSize.width/2;
    
    //Back button
    auto BackButton = ui::Button::create(backButtonImage, backButtonSelectedImage, backButtonImage);
    BackButton->ignoreContentAdaptWithSize(false);
    BackButton->setContentSize(Size(100, 100));
    BackButton->setPosition(Vec2(origin.x + BackButton->getContentSize().width/2, origin.y + visibleSize.height - BackButton->getContentSize().height/2 ));
    BackButton->addTouchEventListener(CC_CALLBACK_2(FriendScene::BackToLoooby, this));
    this->addChild(BackButton);
    
    
    //Username input field
    auto UsernameEditbox = FriendScene::createEditBox("Username", UsernameInputImage);
    UsernameEditbox->setPosition(Vec2(FriendLogo->getPosition().x + 120, FriendLogo->getPosition().y - FriendLogo->getContentSize().height - 50 ));
    UsernameEditbox->setTag(0);
    this->addChild(UsernameEditbox);
    
    //Add button  427 x 359 //Need to fill the callback
    auto AddButton = ui::Button::create(AddButtonImage, AddButtonSelectedImage, AddButtonImage);
    AddButton->ignoreContentAdaptWithSize(false);
    AddButton->setContentSize(Size(427/4, 359/4));
    AddButton->setPosition(Vec2(UsernameEditbox->getPosition().x + UsernameEditbox->getContentSize().width/2 +50, UsernameEditbox->getPosition().y));
    AddButton->addTouchEventListener(CC_CALLBACK_2(FriendScene::SearchCallback, this));
    this->addChild(AddButton);
    
    //==============================================================================================================
    
    //Friend list table
    auto friend_table = FriendTable::create();
    friend_table->setContentSize(Size(1337/4, 750));
    friend_table->ignoreAnchorPointForPosition(false);
    friend_table->setAnchorPoint(Vec2(0.5, 1));
    friend_table->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height));
    this->addChild(friend_table, 1);
    
    //Friend list background
    auto friend_bg = Sprite::create("friend-bg.png");
    friend_bg->setContentSize(Size(visibleSize.width/4 + 100, 600));
    friend_bg->setPosition(Vec2(origin.x + visibleSize.width*3/4, origin.y + visibleSize.height/2));
    this->addChild(friend_bg);
    
    
    
    return true;
}


void FriendScene::BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
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

void FriendScene::SearchCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){// Search user call back.
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:{
            //if(user is not found)
            auto msgLabel = SearchMsgLabel(Search_Msg::Err);
            auto tmp = this->getChildByTag(0); //get Username input editbox object.
            msgLabel->setPosition(Vec2(tmp->getPosition().x , tmp->getPosition().y - tmp->getContentSize().height/2));
            this->addChild(msgLabel);
            /*
            else
             {
             auto msgLabel = SearchMsgLabel(Search_Msg::Success);
             auto tmp = this->getChildByTag(0); //get Username input editbox object.
             msgLabel->setPosition(Vec2(tmp->getPosition().x , tmp->getPosition().y - tmp->getContentSize().height/2));
             this->addChild(msgLabel);
             }
             */
            
            break;
        }
            
        default:
            break;
    }
}

cocos2d::ui::EditBox* FriendScene::createEditBox(const std::string &PlaceHolder, const std::string &ImagePath){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto editBox = cocos2d::ui::EditBox::create(InputFieldSize, ImagePath);
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 默认字体相关
    editBox->setPlaceHolder(PlaceHolder.c_str());
    editBox->setPlaceholderFontName("fonts/arial.ttf");
    editBox->setPlaceholderFontColor(Color3B::BLACK);
    editBox->setPlaceholderFontSize(38);
    
    
    // 编辑框文本相关
    
    editBox->setFontName("fonts/arial.ttf");
    editBox->setFontColor(Color3B::BLACK);
    editBox->setFontSize(38);
    
    return editBox;
}


//Search friend label function =============================================
const std::string FriendScene::ErrMsg = "Error: User is not found!";
const std::string FriendScene::SucMsg = "Friend invention sent!";

cocos2d::Label* FriendScene::SearchMsgLabel(Search_Msg msg){
    switch (msg) {
        case Search_Msg::Err:
        {
            return ErrMsgLabel();
            break;
        }
            
        case Search_Msg::Success:{
            return SucMsgLabel();
            break;
        }
            
        default:
            break;
    }
    
    
}
cocos2d::Label* FriendScene::ErrMsgLabel(){
    auto label = cocos2d::Label::createWithTTF(ErrMsg, "fonts/arial.ttf", 40);
    label->setColor(Color3B::RED);
    return label;
}
cocos2d::Label* FriendScene::SucMsgLabel(){
    auto label = cocos2d::Label::createWithTTF(SucMsg, "fonts/arial.ttf", 40);
    label->setColor(Color3B::GREEN);
    return label;
}
//==========================================================================
//Friend table scroll view
USING_NS_CC_EXT;

void FriendTable::tableCellTouched(TableView *table, TableViewCell *cell){
    CCLOG("you touch cell index = %zd", cell->getIdx());
}

CCSize FriendTable::cellSizeForTable(TableView *table){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(300, 64);
}

//number of friend
ssize_t FriendTable::numberOfCellsInTableView(TableView *table){
    return Fdatabase.get_size();
}

TableViewCell* FriendTable::tableCellAtIndex(TableView *table, ssize_t idx){
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
        cell = new TableViewCell();
        cell->autorelease();
    }
    cell->removeAllChildrenWithCleanup(true);
    
    
   
    //friend name label
    const std::string Name = Fdatabase.get_FriendInfo(idx)->getName();
    auto label = Label::createWithTTF(Name, "fonts/arial.ttf", 40);
    label->setPosition(Vec2(25, 0));
    label->setAnchorPoint(Vec2(0, 0));
    label->setColor(Color3B::BLACK);
    cell->addChild(label);
    
    //friend online status
    const bool status = Fdatabase.get_FriendInfo(idx)->isOnline();

    Sprite* onlineLight;
    
    switch (status) {
        case true:{
            onlineLight = Sprite::create("green-dot.png");
            break;
        }
        case false:{
            onlineLight = Sprite::create("gray-dot.png");
            break;
        }
        default:
            break;
    }
    onlineLight->setContentSize(Size(50, 50));
    onlineLight->setPosition(Vec2(label->getPosition().x+ 250, label->getPosition().y + 20));
    cell->addChild(onlineLight);
    
    
    return cell;
    
}

void FriendTable::scrollViewDidScroll(ScrollView *view){}
void FriendTable::scrollViewDidZoom(ScrollView *view){}

bool FriendTable::init(){
    if(!CCLayer::init()){
        return false;
    }
    /*
    auto backGroundColor = CCLayerColor::create(ccc4(255,255,255, 255)); //RGBA
    this->addChild(backGroundColor, 0);
    */
    
    
    auto visibleSize =  this->getContentSize();
    
    
    //friend list
    TableView * tableview = TableView::create(this, CCSizeMake(300, 480)); //table size
    tableview->setDirection(ScrollView::Direction::VERTICAL); // 只能垂直滑動
    tableview->setDelegate(this);
    tableview->ignoreAnchorPointForPosition(false);
    tableview->setAnchorPoint(Vec2(0, 1));
    tableview->setPosition(Vec2(0, visibleSize.height-170));
    this->addChild(tableview);
    tableview->reloadData();
    
    //friend list label
    auto TopLabel = Label::createWithTTF("Friend list", "fonts/arial.ttf" , 50);
    TopLabel->setColor(Color3B::BLACK);
    TopLabel->setPosition(Vec2(150, visibleSize.height-130));
    this->addChild(TopLabel);
    return true;
    
    
}
