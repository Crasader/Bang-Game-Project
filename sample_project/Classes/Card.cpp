//
//  Card.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#include "Card.hpp"

CardDatabase* CardDatabase::myself = nullptr;

int Card::get_id(){
    return card_id_;
}

const std::string& Card::get_cardName() const{
    return cardName_;
}
int Card::get_suit(){
    return suit_;
}
int Card::get_number(){
    return number_;
}
const std::string& Card::get_Description() const{
    return cardDescription_;
}

void Card::set_id(int id){
    card_id_ = id;
}
void Card::set_Name(std::string &name){
    cardName_ = name;
}
void Card::set_suit(int suit){
    suit_ = suit;
}
void Card::set_number(int number){
    number_ = number;
}
void Card::set_Description(std::string description){
    cardDescription_.assign(description);
}
