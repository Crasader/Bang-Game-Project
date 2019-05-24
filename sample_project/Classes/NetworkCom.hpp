//
//  NetworkCom.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/24.
//

#ifndef NetworkCom_hpp
#define NetworkCom_hpp


#include <nlohmann/json.hpp>
#include "Socket.cpp"
#include <string>
#include <sstream>

using namespace std;
using json = nlohmann::json;

class Client
{
public:
    Client();
    ~Client();
    json userRegisterLogin(int, string);
    json userChangenickname(string);
    json getLoungeinfo();
    json userJoin(bool, int, int);
    json userSetready(bool);
    json userStartgame();
    void playerChoosecharacter(string, string );
    void updateplayerinfo();
    json playerTurn();
    json playerUsecard(int, int);
    void playerShowcard();
    void playerChoosecard(int, int, int);
    void playerDeciderevolt(bool);
    json playerEndusingcard();
    void playerFoldcard(int, int*);
    void endGame();
    void updateUserinfo();
    json userExit();
    json getFriendlist();
    json addFriend(int);
    
    static Client* getInstance();
    
private:
    static Client* myself;
    Socket socket;
    char buf[8192] = {};
    stringstream ss;
    string str;
    string str_var[30] = {"Action", "User ID", "User Name", "Nick Name", "PassWord", "UserMoney", "UserWin", "UserLose", "LoungeAmount", "Ready", "MaxHp", "Hp", "CharacterName", "CardID", "Target", "User_position", "Revolt", "CardAmount", "Lounge", "JoinMethod", "LoungeID", "Shower", "Showee", "ChooseorDiscard", "Chooser", "Choosee", "CardName", "WinorLose", "FriendID", "Friend"};
};


#endif /* NetworkCom_hpp */
