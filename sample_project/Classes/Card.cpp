//
//  Card.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#include "Card.hpp"

int Card::get_id(){
    return card_id_;
}

std::string Card::get_cardName(){
    return cardName_;
}
Suits Card::get_suit(){
    return suit_;
}
int Card::get_number(){
    return number_;
}

void Card::set_id(int id){
    card_id_ = id;
}
void Card::set_Name(std::string &name){
    cardName_ = name;
}
void Card::set_suit(Suits suit){
    suit_ = suit;
}
void Card::set_number(int number){
    number_ = number;
}
