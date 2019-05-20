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
    
};

#endif /* FriendScene_hpp */
