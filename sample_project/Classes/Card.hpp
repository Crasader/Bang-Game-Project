//
//  Card.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#ifndef Card_hpp
#define Card_hpp

#include <string>
enum class Suits{
    spades,//黑桃
    hearts,//紅心
    diamonds,//方塊
    clubs//梅花
};

class Card{
  
public:
    int get_id();
    std::string get_cardName();
    Suits get_suit();
    int get_number();
    
    void set_id(int id);
    void set_Name(std::string &name);
    void set_suit(Suits suit);
    void set_number(int number);
    
private:
    int card_id_;
    std::string cardName_;
    Suits suit_;
    int number_;
};

#endif /* Card_hpp */
