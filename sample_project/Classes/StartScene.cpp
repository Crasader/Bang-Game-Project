//
//  StartScene.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/1.
//

#include "StartScene.hpp"
#include "LobbyScene.hpp"
#include "FirebaseAuthScene.h"
#include "AssisstanceFunc.hpp"
#include "User.hpp"
USING_NS_CC;


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

Scene *StartScene::createScene(){
    return StartScene::create();
}

// on "init" you need to initialize your instance
bool StartScene::init()
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
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(StartScene::menuCloseAppCallback, this));
    
    auto LoginButton = MenuItemFont::create("START", CC_CALLBACK_0(StartScene::Login_callback, this));
    
    LoginButton->setColor(cocos2d::Color3B::BLACK);
    if(LoginButton != nullptr){
        LoginButton->setFontSizeObj(60);
        float x = origin.x + visibleSize.width/2;
        float y = LoginButton->getContentSize().height + 50;
        LoginButton->setPosition(Vec2(x, y));
    }
    
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    menu->addChild(LoginButton);
    this->addChild(menu);
    
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    /*
    auto label = Label::createWithTTF("Bang!", "fonts/Marker Felt.ttf", 100);
    label->setTextColor(cocos2d::Color4B::BLACK);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        
        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    */
    
    auto BangLogo = Sprite::create("bang-logo.png"); // 1844 x 655
    if (BangLogo == nullptr)
    {
        problemLoading("'bang-logo.png'");
    }
    else
    {
        BangLogo->setContentSize(Size(1844/3, 655/3));
        BangLogo->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - BangLogo->getContentSize().height));
        this->addChild(BangLogo);
    }
    
    
   
    return true;
}

/// Handles the user tapping on the close app menu item.
void StartScene::menuCloseAppCallback(Ref* pSender) {
    CCLOG("Cleaning up Auth C++ resources.");
    
    // Close the cocos2d-x game scene and quit the application.
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void StartScene::Login_callback(){
    
    
    firebase::auth::Auth *auth = firebase::auth::Auth::GetAuth(firebase::App::GetInstance());
    if(auth->current_user() != nullptr){ //allready singin
        std::string firebaseUID = auth->current_user()->uid();
        //CCUserDefault::sharedUserDefault()->setStringForKey("firebaseUID", firebaseUID);
        
        unsigned int IntUID = UidHash::BKDRHash(firebaseUID);
        auto user = User::getInstance();
        user->setUID(IntUID);
        user->setFirebaseUID(firebaseUID);
        
        
        
        auto scene = LobbyScene::createScene();
        auto directer = Director::getInstance();
        directer->replaceScene(scene);
        
    }
    else{ // jump to singin scene
        auto scene = FirebaseAuthScene::createScene();
        auto director = Director::getInstance();
        director->replaceScene(scene);
    }
}
    
    




