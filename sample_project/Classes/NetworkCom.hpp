//
//  NetworkCom.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/24.
//

#ifndef NetworkCom_hpp
#define NetworkCom_hpp


#include <nlohmann/json.hpp>
#include "ClientSocket.hpp"
#include <string>
#include <sstream>

using namespace std;
using json = nlohmann::json;

class Client
{
public:
    Client();
    ~Client();
    json userRegisterLogin(unsigned int);
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
    json showDetermineCard(int);
    
    static Client* getInstance();
    
private:
    static Client* myself;
    CClientSocket* socket = nullptr;
    char buf[8192] = {};
    stringstream ss;
    string str;
    const string str_var[4] = {"Action", "User ID", "User Name"};
};


#endif /* NetworkCom_hpp */
