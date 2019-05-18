//
//  RankScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/18.
//

#include "RankScene.hpp"
#include "LobbyScene.hpp"

USING_NS_CC;

// The images for the buttons.
static const std::string kNormalButtonImage = "lobby-btn-fullwidth.png";
static const std::string kSelectedButtonImage = "lobby-btn-fullwidth2.png";
static const std::string kDisabledButtonImage = "lobby-btn-fullwidth.png";

const std::string backButtonImage = "back-icon.png"; //square
const std::string backButtonSelectedImage = "back-icon-click.png";//square
const std::string RankImage = "rank-logo.png"; //943 x 320



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

Scene *RankScene::createScene(){
    return RankScene::create();
}

// on "init" you need to initialize your instance
bool RankScene::init()
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
    BackButton->addTouchEventListener(CC_CALLBACK_2(RankScene::BackToLoooby, this));
    
    
    
    //==============================================================================================================
    
    //Rank Label
    
    auto RankLogo = Sprite::create(RankImage);
    RankLogo->setContentSize(Size(943/4, 320/4));
    RankLogo->setPosition(Vec2(origin.x + visibleSize.width/5, origin.y + visibleSize.height*5/7));
    this->addChild(RankLogo);
    
    
    
    
    return true;
}


void RankScene::BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType type){
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


