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

#ifndef FIREBASE_COCOS_CLASSES_FIREBASE_AUTH_SCENE_H_
#define FIREBASE_COCOS_CLASSES_FIREBASE_AUTH_SCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "FirebaseCocos.h"
#include "FirebaseScene.h"
#include "firebase/auth.h"
#include "firebase/future.h"

#include "PluginFacebook/PluginFacebook.h"  //Facebook SDK
#include "mySdkboxWrap.hpp"

class FirebaseAuthScene : public FirebaseScene, MySdkbox{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    void update(float delta) override;
    
    //void menuCloseAppCallback(cocos2d::Ref *pSender) override;
    
    CREATE_FUNC(FirebaseAuthScene);
private:
    cocos2d::Color3B c3Black = cocos2d::ccc3(0, 0, 0);
    cocos2d::Color3B c3White = cocos2d::ccc3(255, 255, 255);
    cocos2d::Color4B c4Black = cocos2d::ccc4(0, 0, 0, 255);
    cocos2d::Color4B c4White = cocos2d::ccc4(255, 255, 255, 255);
    
    /// A text field where a login email address may be entered.
    cocos2d::ui::TextField* email_text_field_;
    
    /// A text field where a login password may be entered.
    cocos2d::ui::TextField* password_text_field_;
    
    /// A button that uses the given email and password to register a user.
    cocos2d::ui::Button* register_user_button_;
    
    /// A button that uses the given email and password to log in.
    cocos2d::ui::Button* credentialed_sign_in_button_;
    
    cocos2d::ui::Button* facebook_sign_in_button_;
    /// A button that logs in anonymously.
    cocos2d::ui::Button* anonymous_sign_in_button_;
    
    /// A button that logs the user out regardless of how they logged in.
    cocos2d::ui::Button* sign_out_button_;
    
    /// A future that completes some time after attempting to create a new user.
    firebase::Future<firebase::auth::User*> create_user_future_;
    
    /// A future that completes some time after one of the login buttons is
    /// pressed.
    firebase::Future<firebase::auth::User*> sign_in_future_;
    
    /// Keeps track of whether or not the sign in attempt was made anonymously.
    bool anonymous_sign_in_;
    
    //Facebook lisenter callback
    void onLogin(bool isLogin, const std::string& msg);
    void onSharedSuccess(const std::string& message);
    void onSharedFailed(const std::string& message);
    void onSharedCancel();
    void onAPI(const std::string& key, const std::string& jsonData);
    void onPermission(bool isLogin, const std::string& msg);
    void onFetchFriends(bool ok, const std::string& msg);
    void onRequestInvitableFriends( const sdkbox::FBInvitableFriendsInfo& friends );
    void onInviteFriendsWithInviteIdsResult( bool result, const std::string& msg );
    void onInviteFriendsResult( bool result, const std::string& msg );
    void onGetUserInfo( const sdkbox::FBGraphUser& userInfo );
    
};

#endif  // FIREBASE_COCOS_CLASSES_FIREBASE_AUTH_SCENE_H_
