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

void FriendScene::SearchCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
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

//Search friend label function
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
