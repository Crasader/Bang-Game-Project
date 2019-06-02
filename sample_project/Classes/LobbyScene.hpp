//
//  LobbyScene.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/4/22.
//

#ifndef LobbyScene_hpp
#define LobbyScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <nlohmann/json.hpp>
#include "cocos-ext.h"
#include <iostream>
#include <thread>
#include "User.hpp"
#include "NetworkCom.hpp"
#include "WrapInfo.hpp"
#include "ClientSocket.hpp"
class LobbyScene : public cocos2d::Scene{
public:
    static cocos2d::Scene *createScene();
    
    bool init() override;
    
    CREATE_FUNC(LobbyScene);
    
    void getInfoFromServer(){
        
        auto client = Client::getInstance();
        auto user = User::getInstance();
        
        CClientSocket::getInstance()->sendMessage(WrapInfo::WrapRegisterUserInfo(user->getUID()).dump());
        CClientSocket::getInstance()->busyWaitting(0);
        
        
        if(user->getNickName() == ""){
            CClientSocket::getInstance()->sendMessage(WrapInfo::WrapChangeNickName("Test Name").dump());
            CClientSocket::getInstance()->busyWaitting(0);
        }
    }
    
    static void joinLounge(unsigned int lounge_id);
    

    void ListenerStartGame();
    void update(float delta) override;
    
    cocos2d::ui::Button *ReadyButton;
    
    
    
    
private:
    cocos2d::ui::Button *createButton(
                                      bool buttonEnabled, const std::string& buttonTitleText,
                                      const cocos2d::Color3B& buttonColor, const std::string& ImagePath1,const  std::string& ImagePath2, const std::string& ImagePath3);
    void SettingCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void RankCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void FriendCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void ReadyCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    void GameCallback(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    
    using json = nlohmann::json;
    json request_info, r2;
    
    bool isStartGame_ = false;
    static bool intoLounge_;
    
    float nextYPosition;
};

class LoungeInfo{
public:
    
    LoungeInfo(unsigned int id, int amount):ID_(id), userAmount_(amount){};
    
    const unsigned int getID() const{
        return ID_;
    }
    const int getAmount() const{
        return userAmount_;
    }
    
    void setID(unsigned int id){
        ID_ = id;
    }
    void setAmount(int amount){
        userAmount_ = amount;
    }
    
private:
    unsigned int ID_;
    int userAmount_;
};


class LoungeDatabase{//Save all Friend info
public:
    LoungeDatabase():size_(0){};
    
    void set_size(int s){
        size_ = s;
    }
    int get_size(){
        return size_;
    }
    
    void add_Lounge(LoungeInfo *lounge){
        data.push_back(lounge);
        ++size_;
    }
    
    const LoungeInfo* get_LoungeInfo(int idx) const{
        return data[idx];
    }
    
    void clear(){
        for(auto i:data){
            delete i;
        }
        data.clear();
        size_ = 0;
    }
    
    static LoungeDatabase * getInstance(){
        if(LoungeDatabase::myself == nullptr){
            LoungeDatabase::myself = new LoungeDatabase();
        }
        return LoungeDatabase::myself;
    }
    
private:
    static LoungeDatabase * myself;
    int size_;
    std::vector<LoungeInfo*> data;
    
};




class LoungeTable : public cocos2d::CCLayer, public cocos2d::extension::TableViewDelegate, public cocos2d::extension::TableViewDataSource{
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
    
    CREATE_FUNC(LoungeTable);
    
    LoungeDatabase* Ldatabase;
    
    void getLoungListFromServer();
    void updateUserInfo(float delta);
    
private:
    
    cocos2d::extension::TableView * tableview;
};


#endif /* LobbyScene_hpp */
