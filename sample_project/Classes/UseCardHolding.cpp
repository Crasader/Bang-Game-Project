//
//  UseCardHolding.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/5.
//

#include "UseCardHolding.hpp"
#include <iostream>

UseCardHolding* UseCardHolding::myself = nullptr;

UseCardHolding* UseCardHolding::getInstance(){
    if(myself == nullptr){
        myself = new UseCardHolding();
    }
    return myself;
}
int UseCardHolding::get_cardID()const{
    return cardID_;
}
int UseCardHolding::get_target()const{
    return target_;
}
const std::string  UseCardHolding::get_cardName() const{
    return cardName_;
}
void UseCardHolding::set_cardID(int id){
    cardID_ = id;
}
void UseCardHolding::set_target(int target){
    target_ = target;
}
void UseCardHolding::set_cardName(std::string name){
    cardName_ = name;
}

bool UseCardHolding::shouldChooseTarget() const{
    if(ShouldChooseTargetCard.count(cardName_)){
        //std::cout<<cardName_<<std::endl;
        return true;
    }
    else{
        //std::cout<<cardName_<<" flase\n";
        return false;
    }
}

bool UseCardHolding::infoFinish() const{
    if(cardID_ == -1)
        return false;
    
    if(this->shouldChooseTarget()){
        if(target_ != -1){
            return true;
        }
        else
            return false;
    }
    else{
        return true;
    }
}
void UseCardHolding::reset(){
    cardID_ = -1;
    target_ = -1;
    cardName_ = "";
}

UseCardHolding::UseCardHolding(){
    ShouldChooseTargetCard["Bang!"] = 1;
    ShouldChooseTargetCard["Duel"] = 1;
    ShouldChooseTargetCard["Cat Baiou"] = 1;
    ShouldChooseTargetCard["Panic"] = 1;
}
