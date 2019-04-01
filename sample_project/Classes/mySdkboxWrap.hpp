//
//  mySdkboxWrap.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/2.
//

#ifndef mySdkboxWrap_hpp
#define mySdkboxWrap_hpp

#include "PluginFacebook/PluginFacebook.h"  //Facebook SDK
#include <iostream>


class MySdkbox : public sdkbox::FacebookListener {
public:
    static void setListener(sdkbox::FacebookListener *listener){
        sdkbox::PluginFacebook::setListener(listener);
    }
    static void init(){
        sdkbox::PluginFacebook::init();
    }
    static bool isLoggedIn(){
        return sdkbox::PluginFacebook::isLoggedIn();
    }
    static void login(){
        sdkbox::PluginFacebook::login();
    }
    static void logout(){
        sdkbox::PluginFacebook::logout();
    }
    static std::string getAccessToken(){
        return sdkbox::PluginFacebook::getAccessToken();
    }
    
};


#endif /* mySdkboxWrap_hpp */
