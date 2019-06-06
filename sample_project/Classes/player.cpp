//
//  player.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#include "player.hpp"
#include "User.hpp"

PlayerDatabase* PlayerDatabase::myself = nullptr;

int Player::get_Max_hp() const{
    return Max_hp_;
}
int Player::get_hp() const{
    return hp_;
}
int Player::get_team() const{
    return team_;
}
bool Player::is_death() const{
    return death_;
}
int Player::get_add_range() const{
    return add_range_;
}
int Player::get_minus_range() const{
    return minus_range_;
}
bool Player::is_multi_attack() const{
    return multi_attack_;
}

const std::string& Player::get_charName() const{
    return charName_;
}
const std::string& Player::get_PlayerName() const{
    return PlayerName_;
}
int Player::get_holding_card_amount() const{
    return holding_.size();
}
std::vector<int>& Player::get_holding(){
    return holding_;
}

int Player::get_equipment() const{
    return equipment_;
}

int Player::get_position() const{
    return position_;
}

bool Player::isJail() const{
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

void Player::set_team(int team){
    team_ = team;
}
void Player::set_death(bool is_death){
    death_ = is_death;
}
void Player::set_add_range(int range){
    add_range_ = range;
}
void Player::set_minus_range(int range){
    minus_range_ = range;
}
void Player::set_multi_attack(bool multi_attack){
    multi_attack_ = multi_attack;
}

void Player::set_charName( const std::string &Name){
    charName_.assign(Name);
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
