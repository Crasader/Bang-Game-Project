//
//  User.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/24.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <string>
class User{
public:
    User(unsigned int uid, int win, int loss, std::string NickName = ""){
        UID_ = uid;
        NickName_.assign(NickName);
        Win_ = win;
        Lose_ = loss;
    }
    
    unsigned int getUID();
    const std::string & getNickName() const;
    int getWin();
    int getLose();
    const std::string & getFirebaseUID() const;
    int getMoney();
    
    void setUID(unsigned int uid);
    void setNickName(std::string NickName);
    void setWin(int Win);
    void setLose(int Lose);
    void setFirebaseUID(std::string & FUID);
    void setMoney(int money);

    
    static User * getInstance();
private:
    static User * myself;
    unsigned int UID_;
    std::string firebaseUID_;
    std::string NickName_;
    int Win_, Lose_;
    int money_;
};


#endif /* User_hpp */
