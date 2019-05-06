//
//  SettingScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/25.
//

#ifndef SettingScene_hpp
#define SettingScene_hpp


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions//GUI/CCControlExtension/CCControlSlider.h"


class SettingScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    
    
    
    
    CREATE_FUNC(SettingScene);
    
private:
    void BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    cocos2d::ui::Button *createButton(
                                      bool buttonEnabled, const std::string& buttonTitleText,
                                      const cocos2d::Color3B& buttonColor, const std::string& ImagePath1,const  std::string& ImagePath2, const std::string& ImagePath3);
    float nextYPosition;
};

//For audio control
class ControlAudioSlider : public cocos2d::extension::ControlSlider
{
public:
    ControlAudioSlider();
    ~ControlAudioSlider();
    
    typedef std::function<void(ControlAudioSlider*, float, cocos2d::Event*)> audioSliderCallback;
    static ControlAudioSlider* create(const char* bgFile, const char* progressFile, const char* thumbFile);
    
    virtual bool onTouchBegion(cocos2d::Touch* touch, cocos2d::Event* pEvent);
    virtual void onTouchMoved(cocos2d::Touch* touch,  cocos2d::Event* pEvent);
    
    void setValues(float minValue, float maxValue, float value);
    void setCallBack(const audioSliderCallback& callback);
private:
    audioSliderCallback    _callback;
    float _ratio;
};

#endif /* SettingScene_hpp */
