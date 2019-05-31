//
//  LoungeScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/29.
//

#ifndef LoungeScene_hpp
#define LoungeScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <nlohmann/json.hpp>
#include "cocos-ext.h"
#include <iostream>
#include <thread>
#include "NetworkCom.hpp"




class LoungeUserInfo{
public:
    
    LoungeUserInfo(unsigned int id, bool ready):ID_(id), ready_(ready){};
    
    const unsigned int getID() const{
        return ID_;
    }
    const bool isReady() const{
        return ready_;
    }
    
    void setID(unsigned int id){
        ID_ = id;
    }
    void setReady(bool isReady){
        ready_ = isReady;
    }
    
private:
    unsigned int ID_;
    bool ready_;
};


class LoungeUserDatabase{//Save all Friend info
public:
    LoungeUserDatabase():size_(0){};
    
    void set_size(int s){
        size_ = s;
    }
    int get_size(){
        return size_;
    }
    
    void add_User(LoungeUserInfo *user){
        data_.push_back(user);
        ++size_;
    }
    
    bool is_all_user_ready(){
        for(auto i:data_){
            if(! (i->isReady())){
                return false;
            }
        }
        return true;
    }
    
    const LoungeUserInfo* get_LoungeUserInfo(int idx) const{
        
        return data_[idx];
    }
    
    static LoungeUserDatabase * getInstance(){
        if(LoungeUserDatabase::myself == nullptr){
            LoungeUserDatabase::myself = new LoungeUserDatabase();
        }
        return LoungeUserDatabase::myself;
    }
    void clear(){
        for(auto i:data_){
            delete i;
        }
        size_ = 0;
        data_.clear();
    }
    ~LoungeUserDatabase(){
        size_ = 0;
        data_.clear();
        delete myself;
        
    }
    
private:
    static LoungeUserDatabase * myself;
    int size_;
    std::vector<LoungeUserInfo*> data_;
    
};



class LoungeUserTable : public cocos2d::CCLayer, public cocos2d::extension::TableViewDelegate, public cocos2d::extension::TableViewDataSource{
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
    
    CREATE_FUNC(LoungeUserTable);
    
    void getUserListFromServer();
    LoungeUserDatabase *Udatabase;
    
    void updateUserInfo(float delta);
    
private:
    cocos2d::extension::TableView * tableview;
};



#endif /* LoungeScene_hpp */
