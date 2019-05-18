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
#include "audio/include/AudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// The images for the buttons.
static const std::string kNormalButtonImage = "lobby-btn-fullwidth.png";
static const std::string kSelectedButtonImage = "lobby-btn-fullwidth2.png";
static const std::string kDisabledButtonImage = "lobby-btn-fullwidth.png";

const std::string backButtonImage = "back-icon.png"; //square
const std::string backButtonSelectedImage = "back-icon-click.png";//square

const std::string settingImage = "setting-logo.png"; //1258 x 375

constexpr char* bgImage = "mute-bg.png";
constexpr char* progressImage = "mute-progress.png";
constexpr char* thumbImage = "mute-thumb.png";

constexpr int audioID = 999;

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
    auto BackButton = ui::Button::create(backButtonImage, backButtonSelectedImage, backButtonImage);
    BackButton->ignoreContentAdaptWithSize(false);
    BackButton->setContentSize(Size(100, 100));
    BackButton->setPosition(Vec2(origin.x + BackButton->getContentSize().width/2, origin.y + visibleSize.height - BackButton->getContentSize().height/2 ));
    this->addChild(BackButton);
    BackButton->addTouchEventListener(CC_CALLBACK_2(SettingScene::BackToLoooby, this));
    
    //Log out button
    auto LogoutButton = createButton(true, "Logout", cocos2d::Color3B::WHITE, kNormalButtonImage, kSelectedButtonImage, kDisabledButtonImage);
    //nextYPosition = origin.y + visibleSize.height * 1 / 3;
    LogoutButton->setPosition(Vec2(ButtonXPosition, origin.y + 100 ));
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
    this->addChild(LogoutButton);
    
    //BGM Audio slider
    ControlAudioSlider* BGMslider = ControlAudioSlider::create(bgImage, progressImage, thumbImage);
    BGMslider->setPosition(Vec2(visibleSize.width *2/3 , visibleSize.height / 2 +50 ));
    BGMslider->setValues(0, 1.0f, 0.8f);
    BGMslider->setCallBack([&](ControlAudioSlider* sender, float ratio, Event* pEvent)
                        {
                            cocos2d::experimental::AudioEngine::setVolume(audioID, ratio);
                        });
    
    this->addChild(BGMslider);
    
    auto muteIcon = Sprite::create("mute-icon.png");
    muteIcon->setContentSize(Size(80, 80));
    muteIcon->setPosition(Vec2(BGMslider->getPosition().x - BGMslider->getContentSize().width/2 - 50 , BGMslider->getPosition().y));
    this->addChild(muteIcon);
    
    auto BGMLabel = Sprite::create("bgm-btn.png");
    BGMLabel->setContentSize(Size(622/3, 261/3));
    BGMLabel->setAnchorPoint(Vec2(0, 0.5));
    BGMLabel->setPosition(Vec2(muteIcon->getPosition().x + 25, muteIcon->getPosition().y+100));
    this->addChild(BGMLabel);
    
    //Sound_Effect Audio slider
    ControlAudioSlider* SEslider = ControlAudioSlider::create(bgImage, progressImage, thumbImage);
    SEslider->setPosition(Vec2(visibleSize.width *2/3 , BGMslider->getPosition().y - 180));
    SEslider->setValues(0, 1.0f, 0.8f);
    SEslider->setCallBack([&](ControlAudioSlider* sender, float ratio, Event* pEvent)
                           {
                               cocos2d::experimental::AudioEngine::setVolume(audioID, ratio); // change the audio ID
                           });
    
    this->addChild(SEslider);
    
    auto muteIcon2 = Sprite::create("mute-icon.png");
    muteIcon2->setContentSize(Size(80, 80));
    muteIcon2->setPosition(Vec2(SEslider->getPosition().x - SEslider->getContentSize().width/2 - 50 , SEslider->getPosition().y));
    this->addChild(muteIcon2);
    
    auto SELabel = Sprite::create("soundeffect-btn.png");
    SELabel->setContentSize(Size(1186/3, 278/3));
    SELabel->setAnchorPoint(Vec2(0, 0.5));
    SELabel->setPosition(Vec2(muteIcon2->getPosition().x + 25, muteIcon2->getPosition().y+100));
    this->addChild(SELabel);
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




using namespace CocosDenshion;

ControlAudioSlider::ControlAudioSlider()
{
}


ControlAudioSlider::~ControlAudioSlider()
{
}

ControlAudioSlider* ControlAudioSlider::create(const char* bgFile, const char* progressFile, const char* thumbFile)
{
    Sprite *backgroundSprite = Sprite::create(bgFile);
    Sprite *progressSprite = Sprite::create(progressFile);
    Sprite *thumbSprite = Sprite::create(thumbFile);
    Sprite *thumbSelectSprite = Sprite::create(thumbFile);
    
    backgroundSprite->setContentSize(Size(500, 25));
    thumbSprite->setContentSize(Size(35, 35));
    thumbSelectSprite->setContentSize(Size(35, 35));
    
    ControlAudioSlider* pRet = new (std::nothrow) ControlAudioSlider();
    pRet->initWithSprites(backgroundSprite, progressSprite, thumbSprite, thumbSelectSprite);
    
    
    return pRet;
}

bool ControlAudioSlider::onTouchBegion(Touch* touch, Event* pEvent)
{
    bool b = extension::ControlSlider::onTouchBegan(touch, pEvent);
    return b;
}

void ControlAudioSlider::onTouchMoved(Touch* touch, Event* pEvent)
{
    extension::ControlSlider::onTouchMoved(touch, pEvent);
    _ratio = getValue() / getMaximumValue();
    if (_callback)
    {
        _callback(this, _ratio, pEvent);
    }
}

void ControlAudioSlider::setCallBack(const audioSliderCallback& callback)
{
    _callback = callback;
}

void ControlAudioSlider::setValues(float minValue, float maxValue, float value)
{
    this->setMinimumValue(minValue);
    this->setMaximumValue(maxValue);
    this->setValue(value);
}
