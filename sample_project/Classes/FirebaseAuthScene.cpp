// Copyright 2017 Google Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "FirebaseAuthScene.h"
#include "LobbyScene.hpp"


#include <stdarg.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

//#include "PluginFacebook/PluginFacebook.h"
#include "picojson.h"


#include "FirebaseCocos.h"
#include "firebase/auth.h"

#include <iostream>
#include "ScreenLog.h"

USING_NS_CC;

/// Padding for the UI elements.
static const float kUIElementPadding = 10.0;

/// Placeholder labels for the text fields.
static const char* kEmailPlaceholderText = "Email";
static const char* kPasswordPlaceholderText = "Password";

constexpr char* InputImage = "username-input.png";


//In your initialization code, create a firebase::App class.
//firebase::App* app = firebase::App::Create(firebase::AppOptions());

/// Creates the Firebase scene.
Scene* CreateFirebaseScene() {
    return FirebaseAuthScene::createScene();
}

/// Creates the FirebaseAuthScene.
Scene* FirebaseAuthScene::createScene() {
    // Create the scene.
    auto scene = Scene::create();
    
    // Create the layer.
    auto layer = FirebaseAuthScene::create();
    
    // Add the layer to the scene.
    scene->addChild(layer);
    
    return scene;
}

/// Initializes the FirebaseScene.
bool FirebaseAuthScene::init() {
    using firebase::auth::Auth;
    using firebase::auth::Credential;
    using firebase::auth::EmailAuthProvider;
    
    if (!Layer::init()) {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("Initializing the Auth with Firebase API.");
    
    firebase::auth::Auth* auth = firebase::auth::Auth::GetAuth(firebase::App::GetInstance());
    //sdkbox::PluginFacebook::setListener(this); //set facebook listrner
    //sdkbox::PluginFacebook::init(); //initialize sdkbox
    
    MySdkbox::setListener(this);
    MySdkbox::init();
    
    //Set background color
    auto backGroundColor = CCLayerColor::create(ccc4(236, 207, 177, 255)); //RGBA
    this->addChild(backGroundColor, 0);
    
    // Create the Bang label.
    auto BangLabel = Sprite::create("bang-logo.png"); //1844 x 655
    BangLabel->setContentSize(Size(1844/4, 655/4));
    
    BangLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height*3/5));
    this->addChild(BangLabel);
    
    
    xPositon = origin.x + visibleSize.width*2/3;
    nextYPosition = origin.y + visibleSize.height*4/5;
    /*
    const float scrollViewYPosition = nextYPosition -
    BangLabel->getContentSize().height -
    kUIElementPadding * 2;
    
    
    // Create the ScrollView on the Cocos2d thread.
    cocos2d::Director::getInstance()
    ->getScheduler()
    ->performFunctionInCocosThread(
                                   [=]() { this->createScrollView(scrollViewYPosition); });
    
    */
    
    /*
     logMessage("Created the Auth %x class for the Firebase app.",
     static_cast<int>(reinterpret_cast<intptr_t>(auth)));
     */
    
    /*
    // It's possible for current_user() to be non-null if the previous run
    // left us in a signed-in state.
    if (auth->current_user() == nullptr) {
        logMessage("No user signed in at creation time.");
    }
    else{
        logMessage("Current user %s already signed in.",auth->current_user()->display_name().c_str());
    }
    */
    
    //username editbox
    email_editbox = createEditBox(kEmailPlaceholderText, InputImage);
    email_editbox->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
    this->addChild(email_editbox);
    
    //password editbox
    password_editbox = createEditBox(kPasswordPlaceholderText, InputImage);
    password_editbox->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    password_editbox->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    
    this->addChild(password_editbox);
    
    
    credentialed_sign_in_button_ = createButton(ButtonType::Normal , true, "Log in");
    credentialed_sign_in_button_->setTitleFontSize(40);
    credentialed_sign_in_button_->addTouchEventListener(
                                                        [this, auth](Ref* /*sender*/, cocos2d::ui::Widget::TouchEventType type) {
                                                            switch (type) {
                                                                case cocos2d::ui::Widget::TouchEventType::ENDED: {
                                                                    //this->logMessage("Logging in...");
                                                                    std::cout<<"log in \n";

                                                                    const char *email = email_editbox->getText();
                                                                    const char *password = password_editbox->getText();
                                                                    
                                                                    Credential email_cred =
                                                                    EmailAuthProvider::GetCredential(email, password);
                                                                    this->sign_in_future_ = auth->SignInWithCredential(email_cred);
                                                                    
                                                                    break;
                                                                }
                                                                default: {
                                                                    break;
                                                                }
                                                            }
                                                        });
    this->addChild(credentialed_sign_in_button_);
    

    
    register_user_button_ = createButton(ButtonType::Text,true, "Register");
    register_user_button_->setTitleFontSize(30);
    register_user_button_->setTitleColor(cocos2d::Color3B::BLACK);
    auto reg_pos = register_user_button_->getPosition();
    register_user_button_->setPosition(Vec2(reg_pos.x+100, reg_pos.y+50));
    register_user_button_->addTouchEventListener(
                                                 [this, auth](Ref* /**/ , cocos2d::ui::Widget::TouchEventType type) {
                                                     switch (type) {
                                                         case cocos2d::ui::Widget::TouchEventType::ENDED: {
                                                             std::cout<<"register \n";
                                                             //this->logMessage("Registering user...");
                                                             const char* email = email_editbox->getText();
                                                             const char* password = password_editbox->getText();
                                                             this->create_user_future_ = auth->CreateUserWithEmailAndPassword(email, password);
                                                             //this->register_user_button_->setEnabled(false);
                                                             
                                                             if (create_user_future_.status() == firebase::kFutureStatusComplete) {
                                                                 if (create_user_future_.error() == firebase::auth::kAuthErrorNone) {
                                                                     firebase::auth::User* user = *create_user_future_.result();
                                                                     printf("Create user succeeded for email %s\n", user->email().c_str());
                                                                 } else {
                                                                     printf("Created user failed with error '%s'\n", create_user_future_.error_message());
                                                                 }
                                                             }
                                                             break;
                                                         }
                                                             
                                                         default: {
                                                             break;
                                                         }
                                                     }
                                                 });
    this->addChild(register_user_button_);
    
    
    
    
    
    facebook_sign_in_button_ = createButton(ButtonType::Fb, true, "Log in with FB");
    facebook_sign_in_button_->cocos2d::Node::setPosition(Vec2(xPositon, register_user_button_->getPosition().y - (register_user_button_->getContentSize().height/2 + kUIElementPadding) ));//fix the position
    nextYPosition = facebook_sign_in_button_->getPosition().y;//fix the nextYPosition
    facebook_sign_in_button_->setTitleFontSize(40);
    facebook_sign_in_button_->addTouchEventListener(
                                                    [this, auth](Ref* /*sender*/, cocos2d::ui::Widget::TouchEventType type) {
                                                        switch (type) {
                                                            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                                                                
                                                                if ( !MySdkbox::isLoggedIn()) {
                                                                    //this->logMessage("FB Signing in...");
                                                                    //sdkbox::PluginFacebook::login();
                                                                    MySdkbox::login();
                                                                }
                                                                else{
                                                                    //this->logMessage("FB already Signing in, Signing in firebase automatically...");
                                                                    auto FBAccessToken = MySdkbox::getAccessToken();
                                                                    Credential FB_cred = firebase::auth::FacebookAuthProvider::GetCredential(FBAccessToken.c_str());
                                                                    sign_in_future_ = auth->SignInWithCredential(FB_cred);
                                                                    
                                                                }
                                                                
                                                                
                                                                //this->credentialed_sign_in_button_->setEnabled(false);
                                                                //this->sign_out_button_->setEnabled(true);
                                                                break;
                                                            }
                                                            default: {
                                                                break;
                                                            }
                                                        }
                                                    });
    this->addChild(facebook_sign_in_button_);
    /*
    sign_out_button_ = createButton(false, "Sign out");
    sign_out_button_->setTitleFontSize(40);
    sign_out_button_->addTouchEventListener(
                                            [this, auth](Ref* , cocos2d::ui::Widget::TouchEventType type) {
                                                switch (type) {
                                                    case cocos2d::ui::Widget::TouchEventType::ENDED: {
                                                        this->logMessage("Signed out");
                                                        if(MySdkbox::isLoggedIn()){
                                                            MySdkbox::logout();
                                                        }
                                                        auth->SignOut();
                                                        this->credentialed_sign_in_button_->setEnabled(true);
                                                        this->sign_out_button_->setEnabled(false);
                                                        break;
                                                    }
                                                    default: {
                                                        break;
                                                    }
                                                }
                                            });
    this->addChild(sign_out_button_);
    */
    
   
    
    // Schedule the update method for this scene.
    this->scheduleUpdate();
    
    return true;
}

// Called automatically every frame. The update is scheduled in `init()`.
void FirebaseAuthScene::update(float /*delta*/) {
    
    using firebase::auth::AuthError;
    firebase::auth::Auth *auth = firebase::auth::Auth::GetAuth(firebase::App::GetInstance());
    
    /*
    if(auth->current_user() != nullptr){
        std::string firebaseUID = auth->current_user()->uid();
        CCUserDefault::sharedUserDefault()->setStringForKey("firebaseUID", firebaseUID);
        
        auto scene = LobbyScene::createScene();
        auto directer = Director::getInstance();
        directer->replaceScene(scene);
        
    }*/
    
    if (create_user_future_.status() == firebase::kFutureStatusComplete) {
        const AuthError error = static_cast<AuthError>(create_user_future_.error());
        if (error == firebase::auth::kAuthErrorNone) {
            //logMessage("Created new user successfully.");
            AllreadySignin();
        } else {
            //logMessage("ERROR: User creation failed: %d, `%s`", error, //error msg == 8 email was used.sign_in_future_.error_message();
        }
        create_user_future_.Release();
    }
    if (sign_in_future_.status() == firebase::kFutureStatusComplete) {
        const AuthError error = static_cast<AuthError>(sign_in_future_.error());
        if (error == firebase::auth::kAuthErrorNone) {
            //logMessage("Signed in successfully.");
            AllreadySignin(); // jump to Lobby
        }
        else {
            //logMessage("ERROR: Sign in failed: %d, `%s`", error, sign_in_future_.error_message());
            
            this->credentialed_sign_in_button_->setEnabled(true);
        }
        sign_in_future_.Release();
    }
}


void FirebaseAuthScene::AllreadySignin(){//Jump to Lobby

    firebase::auth::Auth *auth = firebase::auth::Auth::GetAuth(firebase::App::GetInstance());
    if(auth->current_user() != nullptr){
        std::string firebaseUID = auth->current_user()->uid();
        CCUserDefault::sharedUserDefault()->setStringForKey("firebaseUID", firebaseUID);
        auto scene = LobbyScene::createScene();
        auto directer = Director::getInstance();
        directer->replaceScene(scene);
        
    }
}


/*********************
 * Facebook callbacks
 *********************/

void FirebaseAuthScene::onLogin(bool isLogin, const std::string& error)
{
    
    if (isLogin)
    {
        firebase::auth::Auth* auth = firebase::auth::Auth::GetAuth(firebase::App::GetInstance());
        auto FBAccessToken = MySdkbox::getAccessToken();
        firebase::auth::Credential FB_cred = firebase::auth::FacebookAuthProvider::GetCredential(FBAccessToken.c_str());
        sign_in_future_ = auth->SignInWithCredential(FB_cred);
    }
    
    //std::string title = "login ";
    //title.append((isLogin ? "success" : "failed"));
    //MessageBox(error.c_str(), title.c_str());
}

void FirebaseAuthScene::onAPI(const std::string& tag, const std::string& jsonData)
{
    CCLOG("##FB onAPI: tag -> %s, json -> %s", tag.c_str(), jsonData.c_str());
    if (tag == "__fetch_picture_tag__") {
        picojson::value v;
        picojson::parse(v, jsonData);
        std::string url = v.get("data").get("url").to_str();
        CCLOG("picture's url = %s", url.data());
        
        //_iconSprite->updateWithUrl(url);
    }
}

void FirebaseAuthScene::onSharedSuccess(const std::string& message)
{
    CCLOG("##FB onSharedSuccess:%s", message.c_str());
    
    MessageBox(message.c_str(), "share success");
}

void FirebaseAuthScene::onSharedFailed(const std::string& message)
{
    CCLOG("##FB onSharedFailed:%s", message.c_str());
    
    MessageBox(message.c_str(), "share failed");
}

void FirebaseAuthScene::onSharedCancel()
{
    CCLOG("##FB onSharedCancel");
    
    MessageBox("", "share cancel");
}

void FirebaseAuthScene::onPermission(bool isLogin, const std::string& error)
{
    CCLOG("##FB onPermission: %d, error: %s", isLogin, error.c_str());
    
    std::string title = "permission ";
    title.append((isLogin ? "success" : "failed"));
    MessageBox(error.c_str(), title.c_str());
}

void FirebaseAuthScene::onFetchFriends(bool ok, const std::string& msg)
{
    CCLOG("##FB %s: %d = %s", __FUNCTION__, ok, msg.data());
    
    MenuItemFont::setFontSize(20);
    static Menu *menu = Menu::create();
    menu->setPositionY(20);
    menu->cleanup();
    
    const std::vector<sdkbox::FBGraphUser>& friends = sdkbox::PluginFacebook::getFriends();
    for (int i = 0; i < friends.size(); i++)
    {
        const sdkbox::FBGraphUser& user = friends.at(i);
        CCLOG("##FB> -------------------------------");
        CCLOG("##FB>> %s", user.uid.data());
        CCLOG("##FB>> %s", user.firstName.data());
        CCLOG("##FB>> %s", user.lastName.data());
        CCLOG("##FB>> %s", user.name.data());
        CCLOG("##FB>> %s", user.isInstalled ? "app is installed" : "app is not installed");
        CCLOG("##FB");
        
        MenuItemFont *item = MenuItemFont::create(user.name, [=](Ref*) {
            sdkbox::FBAPIParam params;
            params["redirect"] = "false";
            params["type"] = "small";
            std::string url(user.uid + "/picture");
            sdkbox::PluginFacebook::api(url, "GET", params, "__fetch_picture_tag__");
        });
        menu->addChild(item);
    }
    if (!menu->getParent()) {
        menu->alignItemsHorizontally();
        addChild(menu);
    }
    
    MessageBox("", "fetch friends");
}

void FirebaseAuthScene::onRequestInvitableFriends( const sdkbox::FBInvitableFriendsInfo& friends )
{
    CCLOG("Request Inviteable Friends Begin");
    for (auto it = friends.begin(); it != friends.end(); ++it) {
        //_inviteableUsers.push_back(*it);
        CCLOG("Invitable friend: %s", it->getName().c_str());
    }
    CCLOG("Request Inviteable Friends End");
    /*
     if (0 == _inviteableUsers.size()) {
     CCLOG("WARNING! Your Invitable Friends number is 0");
     }
     */
    //showInviteableFriends();
}

void FirebaseAuthScene::onInviteFriendsWithInviteIdsResult( bool result, const std::string& msg )
{
    CCLOG("on invite friends with invite ids %s= '%s'", result?"ok":"error", msg.c_str());
}

void FirebaseAuthScene::onInviteFriendsResult( bool result, const std::string& msg )
{
    CCLOG("on invite friends %s= '%s'", result?"ok":"error", msg.c_str());
}

void FirebaseAuthScene::onGetUserInfo( const sdkbox::FBGraphUser& userInfo )
{
    CCLOG("Facebook id:'%s' name:'%s' last_name:'%s' first_name:'%s' email:'%s' installed:'%d'",
          userInfo.getUserId().c_str(),
          userInfo.getName().c_str(),
          userInfo.getFirstName().c_str(),
          userInfo.getLastName().c_str(),
          userInfo.getEmail().c_str(),
          userInfo.isInstalled ? 1 : 0
          );
}

