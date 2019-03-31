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

#include <stdarg.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

#include "PluginFacebook/PluginFacebook.h"
#include "picojson.h"


#include "FirebaseCocos.h"
#include "firebase/auth.h"

#include <iostream>
#include "ScreenLog.h"

USING_NS_CC;

/// Padding for the UI elements.
static const float kUIElementPadding = 10.0;

/// Placeholder labels for the text fields.
static const char* kEmailPlaceholderText = "Account : email/username";
static const char* kPasswordPlaceholderText = "Password: ";


//In your initialization code, create a firebase::App class.
firebase::App* app = firebase::App::Create(firebase::AppOptions());

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
    
    firebase::auth::Auth* auth = firebase::auth::Auth::GetAuth(app);
    sdkbox::PluginFacebook::setListener(this);
    sdkbox::PluginFacebook::init(); //initialize sdkbox

  // Create the Firebase label.
  auto firebaseLabel =
      Label::createWithTTF("Firebase Auth", "fonts/Marker Felt.ttf", 40);
  nextYPosition =
      origin.y + visibleSize.height - firebaseLabel->getContentSize().height;
  firebaseLabel->setPosition(
      cocos2d::Vec2(origin.x + visibleSize.width / 2, nextYPosition));
  this->addChild(firebaseLabel, 1);

  const float scrollViewYPosition = nextYPosition -
                                    firebaseLabel->getContentSize().height -
                                    kUIElementPadding * 2;
  // Create the ScrollView on the Cocos2d thread.
  cocos2d::Director::getInstance()
      ->getScheduler()
      ->performFunctionInCocosThread(
          [=]() { this->createScrollView(scrollViewYPosition); });

  logMessage("Created the Auth %x class for the Firebase app.",
             static_cast<int>(reinterpret_cast<intptr_t>(auth)));

  // It's possible for current_user() to be non-null if the previous run
  // left us in a signed-in state.
  if (auth->current_user() == nullptr) {
    logMessage("No user signed in at creation time.");
  } else {
    logMessage("Current user %s already signed in, so signing them out.",
               auth->current_user()->display_name().c_str());
  }

  email_text_field_ = createTextField(kEmailPlaceholderText);

  this->addChild(email_text_field_);

  password_text_field_ = createTextField(kPasswordPlaceholderText);
  
  this->addChild(password_text_field_);

  register_user_button_ = createButton(true, "Register user");
    register_user_button_->setTitleFontSize(40);
  register_user_button_->addTouchEventListener(
      [this, auth](Ref* /*sender*/, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
          case cocos2d::ui::Widget::TouchEventType::ENDED: {
            this->logMessage("Registering user...");
            const char* email = email_text_field_->getString().c_str();
            const char* password = password_text_field_->getString().c_str();
            this->create_user_future_ =
            auth->CreateUserWithEmailAndPassword(email, password);
            this->register_user_button_->setEnabled(false);
              
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

  credentialed_sign_in_button_ = createButton(true, "Sign in");
    credentialed_sign_in_button_->setTitleFontSize(40);
  credentialed_sign_in_button_->addTouchEventListener(
      [this, auth](Ref* /*sender*/, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
          case cocos2d::ui::Widget::TouchEventType::ENDED: {
            this->logMessage("Signing in...");
            const char* email = email_text_field_->getString().c_str();
            const char* password = password_text_field_->getString().c_str();
            Credential email_cred =
                EmailAuthProvider::GetCredential(email, password);
            this->sign_in_future_ = auth->SignInWithCredential(email_cred);
            this->credentialed_sign_in_button_->setEnabled(false);
            this->sign_out_button_->setEnabled(true);
            this->anonymous_sign_in_ = false;
            break;
          }
          default: {
            break;
          }
        }
      });
  this->addChild(credentialed_sign_in_button_);
    
    
    
   facebook_sign_in_button_ = createButton(true, "FB Sign in");
    facebook_sign_in_button_->setTitleFontSize(40);
    facebook_sign_in_button_->addTouchEventListener(
    [this, auth](Ref* /*sender*/, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::ENDED: {
                
                if (!sdkbox::PluginFacebook::isLoggedIn()) {
                    
                    this->logMessage("FB Signing in...");
                    sdkbox::PluginFacebook::login();
                    
                    auto FBAccessToken = sdkbox::PluginFacebook::getAccessToken();
                    //auto cre = CCUserDefault::sharedUserDefault()->getStringForKey("AccessToken");
                
                    Credential FB_cred = firebase::auth::FacebookAuthProvider::GetCredential(FBAccessToken.c_str());
                    sign_in_future_ = auth->SignInWithCredential(FB_cred);
                    
                }
                else{
                    this->logMessage("FB auto Signing in...");
                    auto FBAccessToken = sdkbox::PluginFacebook::getAccessToken();
                    //auto cre = CCUserDefault::sharedUserDefault()->getStringForKey("AccessToken");
                    Credential FB_cred = firebase::auth::FacebookAuthProvider::GetCredential(FBAccessToken.c_str());
                    sign_in_future_ = auth->SignInWithCredential(FB_cred);
                    

                }
                //const char* email = email_text_field_->getString().c_str();
                //const char* password = password_text_field_->getString().c_str();
                
                this->credentialed_sign_in_button_->setEnabled(false);
                this->sign_out_button_->setEnabled(true);
                break;
            }
            default: {
                break;
            }
        }
    });
    this->addChild(facebook_sign_in_button_);

  sign_out_button_ = createButton(false, "Sign out");
    sign_out_button_->setTitleFontSize(40);
  sign_out_button_->addTouchEventListener(
      [this, auth](Ref* /*sender*/, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) {
          case cocos2d::ui::Widget::TouchEventType::ENDED: {
            this->logMessage("Signed out");
              if(sdkbox::PluginFacebook::isLoggedIn()){
                  sdkbox::PluginFacebook::logout();
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

  // Create the close app menu item.
  auto closeAppItem = MenuItemImage::create(
      "CloseNormal.png", "CloseSelected.png",
      CC_CALLBACK_1(FirebaseScene::menuCloseAppCallback, this));
  closeAppItem->setContentSize(cocos2d::Size(25, 25));
  // Position the close app menu item on the top-right corner of the screen.
  closeAppItem->setPosition(cocos2d::Vec2(
      origin.x + visibleSize.width - closeAppItem->getContentSize().width / 2,
      origin.y + visibleSize.height -
          closeAppItem->getContentSize().height / 2));

  // Create the Menu for touch handling.
  auto menu = Menu::create(closeAppItem, NULL);
  menu->setPosition(cocos2d::Vec2::ZERO);
  this->addChild(menu, 1);


  // Schedule the update method for this scene.
  this->scheduleUpdate();

  return true;
}

// Called automatically every frame. The update is scheduled in `init()`.
void FirebaseAuthScene::update(float /*delta*/) {
    
  using firebase::auth::AuthError;
  if (create_user_future_.status() == firebase::kFutureStatusComplete) {
    const AuthError error = static_cast<AuthError>(create_user_future_.error());
    if (error == firebase::auth::kAuthErrorNone) {
      logMessage("Created new user successfully.");
    } else {
      logMessage("ERROR: User creation failed: %d, `%s`", error,
                 sign_in_future_.error_message());
    }
    this->register_user_button_->setEnabled(true);
    create_user_future_.Release();
  }
  if (sign_in_future_.status() == firebase::kFutureStatusComplete) {
    const AuthError error = static_cast<AuthError>(sign_in_future_.error());
    if (error == firebase::auth::kAuthErrorNone) {
      logMessage("Signed in successfully.");
    
        
        
    } else {
      logMessage("ERROR: Sign in failed: %d, `%s`", error,
                 sign_in_future_.error_message());
      if (this->anonymous_sign_in_) {
        logMessage("You may need to enable anonymous login in the Firebase "
                   "Console.");
        logMessage("(In the console, navigate to Authentication > "
                   "Sign-in Method > Anonymous and click Enable)");
      }
      this->credentialed_sign_in_button_->setEnabled(true);
//      this->anonymous_sign_in_button_->setEnabled(true);
      //this->sign_out_button_->setEnabled(false);
    }
    sign_in_future_.Release();
  }
}

/// Handles the user tapping on the close app menu item.
void FirebaseAuthScene::menuCloseAppCallback(Ref* pSender) {
  CCLOG("Cleaning up Auth C++ resources.");

  // Close the cocos2d-x game scene and quit the application.
  Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}

/*********************
 * Facebook callbacks
 *********************/
void FirebaseAuthScene::onLogin(bool isLogin, const std::string& error)
{
    INFO("##FB onLogin: %s, msg: %s", isLogin ? "yes":"no", error.c_str());
    
    if (isLogin)
    {
        firebase::auth::Auth* auth = firebase::auth::Auth::GetAuth(app);
        auto FBAccessToken = sdkbox::PluginFacebook::getAccessToken();
        //auto cre = CCUserDefault::sharedUserDefault()->getStringForKey("AccessToken");
        
        firebase::auth::Credential FB_cred = firebase::auth::FacebookAuthProvider::GetCredential(FBAccessToken.c_str());
        sign_in_future_ = auth->SignInWithCredential(FB_cred);
    }
    
    std::string title = "login ";
    title.append((isLogin ? "success" : "failed"));
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
