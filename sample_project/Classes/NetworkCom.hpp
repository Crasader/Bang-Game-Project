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
    json userChangenickname(const string& );
    //json getLoungeinfo();
    json userJoin(bool join,unsigned int loungeId,unsigned int userId);
    json userSetready(bool);
    json userStartgame();
    void playerChoosecharacter(const string &charname);
    void updateplayerinfo();
    json playerTurn();
    
    void playerShowcard();
    void playerChoosecard(int, int, int);
    void playerDeciderevolt(bool);
    json playerEndusingcard();
    void playerFoldcard(int, int*);
    void endGame();
    void updateUserinfo();
    json userExit();
    json getFriendlist();
   // json addFriend(int);
    json showDetermineCard(int);
    //json getLoungeUserInfo(); //action 22
    static void HandleAction(const string & Message);
    
    
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
