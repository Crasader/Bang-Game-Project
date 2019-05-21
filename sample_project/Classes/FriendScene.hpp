//
//  FriendScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/18.
//

#ifndef FriendScene_hpp
#define FriendScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "nlohmann/json.hpp"

#include <string>
#include <vector>

//#include <nlohmann/json.hpp>

enum class Search_Msg{
    Err, Success
};

class FriendScene : public cocos2d::Scene{
public:
    
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    
    
    CREATE_FUNC(FriendScene);
    
private:
    cocos2d::ui::EditBox *createEditBox(const std::string &PlaceHolder, const std::string &ImagePath);
    void BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void SearchCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    //--------------------------------------------
    cocos2d::Label *SearchMsgLabel(Search_Msg msg);
    cocos2d::Label *ErrMsgLabel();
    cocos2d::Label *SucMsgLabel();
    //--------------------------------------------
    static const std::string ErrMsg;//search friend error msg
    static const std::string SucMsg;//search friend success msg
};

class FriendInfo{
public:
    FriendInfo(){
        online_ = false;
        name_ = "no name";
        UID_ = 0;
    }
    FriendInfo(const std::string &name, bool online){
        online_ = online;
        name_ = name;
    }
    FriendInfo(const std::string &name, bool online, unsigned int id){
        online_ = online;
        name_ = name;
        UID_ = id;
    }
    
    const bool isOnline() const {
        return online_;
    }
    const std::string getName() const{
        return name_;
    }
    const unsigned int getUID(){
        return UID_;
    }
    
    void setName(const std::string &name){
        name_ = name;
    }
    void setOnline(bool online){
        online_ = online;
    }
    
private:
    bool online_;
    std::string name_;
    unsigned int UID_;
    
};

class FriendDatabase{//Save all Friend info
public:
    FriendDatabase(){
        size_ = 1;//test
        data.push_back(new FriendInfo("testName", true)); //test
    }
    
    void set_size(int s);
    int get_size(){
        return size_;
    }
    
    void add_friend(FriendInfo *f){
        data.push_back(f);
        ++size_;
    }
    
    const FriendInfo* get_FriendInfo(int idx) const{
        return data[idx];
    }
    
private:
    int size_;
    std::vector<FriendInfo*> data;
    
};


class FriendTable : public cocos2d::CCLayer, public cocos2d::extension::TableViewDelegate, public cocos2d::extension::TableViewDataSource{
public:
    
    virtual bool init();
    
    //触摸到某个cell的事件
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
    // 定制单元格的尺寸
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::TableView *table);
    
    //定制每个cell的内容
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    
    //确定这个tableview的cell行数
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    // TableViewDelegate 继承自 ScrollViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
    
    CREATE_FUNC(FriendTable);
    
    FriendDatabase Fdatabase;
    
};





#endif /* FriendScene_hpp */
