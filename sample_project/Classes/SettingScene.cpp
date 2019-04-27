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
static const std::string kNormalButtonImage = "ButtonS1.png";
static const std::string kSelectedButtonImage = "ButtonS2.png";
static const std::string kDisabledButtonImage = "ButtonS1.png";

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
    auto BackButton = createButton(true, "Back", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    BackButton->cocos2d::Node::setPosition(origin.x, origin.y + visibleSize.height - BackButton->getContentSize().height );
    BackButton->setTitleOffset(50, 0);
    this->addChild(BackButton);
    BackButton->addTouchEventListener(CC_CALLBACK_2(SettingScene::BackToLoooby, this));
    
    //Log out button
    auto LogoutButton = createButton(true, "Logout", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    nextYPosition = origin.y + visibleSize.height * 2 / 3;
    LogoutButton->setPosition(Vec2(ButtonXPosition, nextYPosition));
    this->addChild(LogoutButton);
    
    LogoutButton->addTouchEventListener([this](Ref* /*sender*/, cocos2d::ui::Widget::TouchEventType type) {
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

    
    auto GSettingLabel = Label::createWithTTF("Game Setting", "fonts/arial.ttf", 100);
    GSettingLabel->setColor(Color3B::BLACK);
    GSettingLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - GSettingLabel->getContentSize().height));
    
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
