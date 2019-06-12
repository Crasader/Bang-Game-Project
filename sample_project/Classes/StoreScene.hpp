//
//  StoreScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/12.
//

#ifndef StoreScene_hpp
#define StoreScene_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "nlohmann/json.hpp"

#include <string>
#include <vector>




class CardInfo{
public:
    CardInfo(unsigned int id, int cost, const std::string name, const std::string des):id_(id), cost_(cost), name_(name), description_(des){};
    unsigned int get_ID() const{
        return id_;
    }
    const std::string get_Name() const{
        return name_;
    }
    const std::string get_Description() const{
        return description_;
    }
    int get_Cost() const {
        return cost_;
    }
    
    
private:
    unsigned int id_;
    std::string name_, description_;
    int cost_;
};


class StoreDatabase{
public:
    int Size() const{
        return size_;
    }
    void add_card(CardInfo *c){
        data.push_back(c);
        ++size_;
    }
    
    const CardInfo* get_CardInfo(int idx) const{
        return data[idx];
    }
    
    static StoreDatabase* getInstance(){
        if(StoreDatabase::myself == nullptr){
            StoreDatabase::myself = new StoreDatabase();
        }
        return StoreDatabase::myself;
    }
    
    void clear(){
        size_ = 0;
        for(auto i:data){
            delete i;
        }
        data.clear();
    }
    
    
private:
    static StoreDatabase* myself;
    int size_;
    std::vector<CardInfo*> data;
};

class StoreTable : public cocos2d::CCLayer, public cocos2d::extension::TableViewDelegate, public cocos2d::extension::TableViewDataSource{
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
    
    CREATE_FUNC(StoreTable);
    
    
    StoreDatabase* Sdatabase;
    void getStoreFromServer();
    //void updateUserInfo(float delta);
    
private:
    cocos2d::extension::TableView * tableview;
};


class StoreScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    void update(float);
    
    CREATE_FUNC(StoreScene);
    
    void set_description_L(const std::string str);
    
private:
    Label * desL_;
    void BackToLoooby(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    
    
};
#endif /* StoreScene_hpp */
