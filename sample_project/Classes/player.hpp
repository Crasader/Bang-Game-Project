//
//  player.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <string>
#include <vector>

class Player{
public:
    int get_Max_hp();
    int get_hp();
    const std::string get_charName();
    int get_holding_card_amount();
    const std::vector<int>& get_holding() const;
    int get_equipment();
    int get_position();
    
    void set_Max_hp(int hp);
    void set_hp(int hp);
    void set_charName(std::string &Name);
    void set_holding_card_amount(int amount);
    bool use_card(int card);
    void add_card(int card);
    void set_position(int pos);
    
    
private:
    int Max_hp_;
    int hp_;
    std::string charName_;
    int holding_card_amount_;
    std::vector<int> holding_;
    int equipment_;
    int position_;
};

#endif /* player_hpp */
