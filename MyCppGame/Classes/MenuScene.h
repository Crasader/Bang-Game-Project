//
//  MenuScene.h
//  MyCppGame-mobile
//
//  Created by Guan Ying Chen on 2019/3/28.
//

#ifndef MenuScene_h
#define MenuScene_h

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    
    
    void starMenuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif /* MenuScene_h */
