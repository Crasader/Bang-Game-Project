//
//  NetworkCom.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/24.
//

#include "NetworkCom.hpp"

#include <iostream>


Client* Client::myself = nullptr;

Client* Client::getInstance(){
    if(Client::myself == nullptr){
        Client::myself = new Client();
    }
    return Client::myself;
}
Client::Client()
{
    socket.Init();
    socket.Create(AF_INET, SOCK_STREAM, 0);
    socket.Connect("104.199.215.104", 28716);
}
Client::~Client()
{
    socket.Close();
    socket.Clean();
}
json Client::userRegisterLogin(int userId, string nickName)
{
    json j;
    j["Action"] = 0;
    j["User ID"] = userId;
    str = j.dump();
    socket.Send(str.c_str(), str.size(), 0);
    socket.Recv(buf, 8192, 0);
    json s;
    std::cerr<<buf;
    s.parse(buf);
    return s;
}
json Client::userChangenickname(string nickname)
{
    json j;
    j["Action"] = 1;
    j["Nick Name"] = nickname;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
json Client::getLoungeinfo()
{
    json j;
    j["Action"] = 2;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
json Client::userJoin(bool join, int loungeId, int userId)
{
    json j;
    j["Action"] = 3;
    j["Join Method"] = join;
    j["Lounge ID"] = loungeId;
    j["User ID"] = userId;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
json Client::userSetready(bool is_ready)
{
    json j;
    j["Action"] = 4;
    j["Ready"] = is_ready;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
json Client::userStartgame()
{
    json j;
    j["Action"] = 5;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
void Client::playerChoosecharacter(string charname1, string charname2)
{
    json j;
    j["Action"] = 6;
    j["Character Name 0"] = charname1;
    j["Character Name 1"] = charname2;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
void Client::updateplayerinfo()
{
    json j;
    j[str_var[0]] = 7;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
json Client::playerTurn()
{
    json j;
    j[str_var[0]] = 8;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
json Client::playerUsecard(int cardId, int target)
{
    json j;
    j[str_var[0]] = 9;
    j[str_var[13]] = cardId;
    j[str_var[14]] = target;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
void Client::playerShowcard()
{
    json j;
    j[str_var[0]] = 10;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
void Client::playerChoosecard(int chooser, int choosee, int cardId)
{
    json j;
    j[str_var[0]] = 11;
    j[str_var[15]] = chooser;
    j[str_var[15]] = choosee;
    j[str_var[13]] = cardId;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
void Client::playerDeciderevolt(bool revolt)
{
    json j;
    j[str_var[0]] = 12;
    j[str_var[16]] = revolt;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
json Client::playerEndusingcard()
{
    json j;
    j[str_var[0]] = 13;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
void Client::playerFoldcard(int amount, int *cardId)
{
    json j;
    j[str_var[0]] = 14;
    j[str_var[17]] = amount;
    string s;
    for(int i = 0; i < amount; i++)
    {
        s = str_var[13] + '_';
        s += ('0' + i);
        j[s] = cardId[i];
    }
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
void Client::endGame()
{
    json j;
    j[str_var[0]] = 15;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
void Client::updateUserinfo()
{
    json j;
    j[str_var[0]] = 16;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    return;
}
json Client::userExit()
{
    json j;
    j[str_var[0]] = 17;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
json Client::getFriendlist()
{
    json j;
    j[str_var[0]] = 18;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
json Client::addFriend(int friendId)
{
    json j;
    j[str_var[0]] = 19;
    j[str_var[1]] = friendId;
    ss << j;
    ss >> str;
    socket.Send(str.c_str(), str.size(), 0);
    ss.str("");
    ss.clear();
    socket.Recv(buf, 8192, 0);
    json s;
    s.parse(buf);
    return s;
}
