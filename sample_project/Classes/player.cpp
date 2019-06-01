//
//  player.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#include "player.hpp"
#include "User.hpp"

PlayerDatabase* PlayerDatabase::myself = nullptr;

int Player::get_Max_hp(){
    return Max_hp_;
}
int Player::get_hp(){
    return hp_;
}
const std::string& Player::get_charName() const{
    return charName_;
}
const std::string& Player::get_PlayerName() const{
    return PlayerName_;
}
int Player::get_holding_card_amount(){
    return holding_card_amount_;
}
const std::vector<int>& Player::get_holding() const{
    return holding_;
}

int Player::get_equipment(){
    return equipment_;
}

int Player::get_position(){
    return position_;
}

bool Player::isJail(){
    return isJail_;
}

void Player::set_PlayerName(const std::string &Name){
    PlayerName_ = Name;
}

void Player::set_Max_hp(int max_hp){
    Max_hp_ = max_hp;
}

void Player::set_hp(int hp){
    hp_ = hp;
}

void Player::set_charName( const std::string &Name){
    charName_.assign(Name);
}

void Player::set_holding_card_amount(int amount){
    holding_card_amount_ = amount;
}

bool Player::use_card(int card){
    for(auto i = holding_.begin(); i!=holding_.end(); i++){
        if(*i == card){
            holding_.erase(i);
            return true;
        }
    }
    return false;
}

void Player::add_card(int card){
    holding_.push_back(card);
}

void Player::set_position(int pos){
    position_ = pos;
}

void Player::set_Jail(bool isJail){
    isJail_ = isJail;
}
