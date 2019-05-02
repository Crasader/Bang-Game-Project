//
//  SettingScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/25.
//

#include "SettingScene.hpp"
#include "LobbyScene.hpp"
#include "mySdkboxWrap.hpp"
#include "FirebaseAuthScene.h"

USING_NS_CC;

// The images for the buttons.
static const std::string kNormalButtonImage = "lobby-btn-fullwidth.png";
static const std::string kSelectedButtonImage = "lobby-btn-fullwidth2.png";
static const std::string kDisabledButtonImage = "lobby-btn-fullwidth.png";

const std::string backButtonImage = "back-icon.png"; //square
const std::string settingImage = "setting-logo.png"; //1258 x 375

/// Padding for the UI elements.
static const float kUIElementPadding = -20;

/// The title text size for the Firebase buttons.
static const float kButtonTitleFontSize = 45.0;

/// The content size for the Firebase buttons.
static const cocos2d::Size kButtonContentSize = cocos2d::Size(400, 100);





// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

Scene *SettingScene::createScene(){
    return SettingScene::create();
}

// on "init" you need to initialize your instance
bool SettingScene::init()
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
    //Button X pos  (middle of window)
    const float  ButtonXPosition = origin.x + visibleSize.width/2;
    
    //Back button
    auto BackButton = ui::Button::create(backButtonImage, backButtonImage, backButtonImage);
    BackButton->ignoreContentAdaptWithSize(false);
    BackButton->setContentSize(Size(100, 100));
    BackButton->setPosition(Vec2(origin.x + BackButton->getContentSize().width/2, origin.y + visibleSize.height - BackButton->getContentSize().height/2 ));
    this->addChild(BackButton);
    BackButton->addTouchEventListener(CC_CALLBACK_2(SettingScene::BackToLoooby, this));
    
    //Log out button
    auto LogoutButton = createButton(true, "Logout", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    nextYPosition = origin.y + visibleSize.height * 1 / 3;
    LogoutButton->setPosition(Vec2(ButtonXPosition, nextYPosition));
    this->addChild(LogoutButton);
    
    LogoutButton->addTouchEventListener([this](Ref* , cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                if(MySdkbox::isLoggedIn()){//logout FB
                    MySdkbox::logout();
                }
                firebase::auth::Auth *auth = firebase::auth::Auth::GetAuth(firebase::App::GetInstance());
                if(auth->current_user() != nullptr){ //logout firebase;
                    auth->SignOut();
                }
                auto scene = FirebaseAuthScene::createScene();
                auto director = Director::getInstance();
                director->replaceScene(scene);
            }
            default: {
                break;
            }
        }
    });
    
    //==============================================================================================================
    
    //Game Setting Label

    
    auto GSettingLabel = Sprite::create(settingImage);
    GSettingLabel->setContentSize(Size(1258/4, 375/4));
    GSettingLabel->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height*5/7));
    
    this->addChild(GSettingLabel);
    
    
    
    
    return true;
}


cocos2d::ui::Button* SettingScene::createButton(
                                              bool buttonEnabled, const std::string& buttonTitleText,
                                              const cocos2d::Color3B& buttonColor, const std::string& ImagePath1, const std::string& ImagePath2, const std::string& ImagePath3) {
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    cocos2d::ui::Button* button = cocos2d::ui::Button::create(
                                                              ImagePath1, ImagePath2, ImagePath3);
    button->setEnabled(buttonEnabled);
    button->setTitleColor(buttonColor);
    button->setTitleText(buttonTitleText);
    button->setTitleFontSize(kButtonTitleFontSize);
    button->ignoreContentAdaptWithSize(false);
    button->setContentSize(kButtonContentSize);
    nextYPosition -= button->getContentSize().height + kUIElementPadding;
    return button;
}

void SettingScene::BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
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
