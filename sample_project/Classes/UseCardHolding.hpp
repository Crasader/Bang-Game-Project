//
//  UseCardHolding.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/5.
//

#ifndef UseCardHolding_hpp
#define UseCardHolding_hpp

#include <string>
#include <map>

class UseCardHolding{
    
public:
    UseCardHolding();
    
    int get_cardID() const;
    int get_target() const;
    const std::string get_cardName() const;
    
    
    
    void set_cardID(int id);
    void set_target(int target);
    void set_cardName(std::string name);
    
    static UseCardHolding* getInstance();
    
    bool shouldChooseTarget() const;
    
    bool infoFinish() const;
    void reset();
private:
    
    
    std::map<std::string, int> ShouldChooseTargetCard;
    static UseCardHolding* myself;
    std::string cardName_ = "";
    int cardID_ = -1;
    int target_ = -1;
};


#endif /* UseCardHolding_hpp */
