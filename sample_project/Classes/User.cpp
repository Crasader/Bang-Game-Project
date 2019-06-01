//
//  User.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/24.
//

#include "User.hpp"


User * User::myself = nullptr;
unsigned int User::getWhereLounge(){
    return whereLoinge_;
}
unsigned int User::getUID(){
    return UID_;
}
const std::string & User::getNickName() const{
    return NickName_;
}
int User::getWin(){
    return Win_;
}
int User::getLose(){
    return Lose_;
}
int User::getMoney(){
    return money_;
}

const std::string & User::getFirebaseUID() const{
    return firebaseUID_;
}
void User::setUID(unsigned int uid){
    UID_ = uid;
}
void User::setNickName(std::string NickName){
    NickName_.assign(NickName);
}
void User::setWin(int Win){
    Win_ = Win;
}
void User::setLose(int Lose){
    Lose_ = Lose;
}

void User::setWhereLounge(unsigned int id){
    whereLoinge_ = id;
}
void User::setFirebaseUID(std::string & FUID){
    firebaseUID_ = FUID;
}
User * User::getInstance()
{
    if(User::myself == nullptr)
    {
        User::myself = new User(0, 0, 0);
    }
    return User::myself;
}
void User::setMoney(int money){
    money_ = money;
}
