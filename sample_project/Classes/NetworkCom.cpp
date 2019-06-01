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
    if( socket == nullptr ){
        socket = new CClientSocket(28716, "104.199.215.104");
    }
}
Client::~Client()
{
    delete socket;
}
json Client::getJBuffer(){
    json re;
    if(socket->GetReceived()){
        re = json::parse(socket->GetBuffer());
        socket->SetReceived(false);
    }
    return re;
}

json Client::userRegisterLogin(unsigned int userId)
{
    json se ,re;
    se[str_var[0]] = 0;
    se[str_var[1]] = userId;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}

json Client::userChangenickname(const string& nickname)
{
    json se ,re;
    se[str_var[0]] = 1;
    se["Nick Name"] = nickname;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    
    return re;
}
json Client::getLoungeinfo()
{
    json se ,re;
    se[str_var[0]] = 2;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}
json Client::userJoin(bool join,unsigned int loungeId,unsigned int userId)
{
    json se ,re;
    se[str_var[0]] = 3;
    se["Join Method"] = join;
    se["Lounge ID"] = loungeId;
    se[str_var[1]] = userId;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}
json Client::userSetready(bool is_ready)
{
    json se ,re;
    se[str_var[0]] = 4;
    se["Ready"] = is_ready;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}
json Client::userStartgame()
{
    json se ,re;
    se[str_var[0]] = 5;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}
void Client::playerChoosecharacter(const string &charname)
{
    json se;
    se[str_var[0]] = 6;
    se["Choose Character Name"] = charname;
    socket->sendMessage(se.dump());
}
void Client::updateplayerinfo()
{
    
}
json Client::playerTurn()
{
    json se ,re;
    se[str_var[0]] = 8;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}
json Client::playerUsecard(int cardId, int target)
{
    json se ,re;
    se[str_var[0]] = 9;
    se["Card ID"] = cardId;
    se["Target Position"] = target;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}
void Client::playerShowcard()
{
    
}
void Client::playerChoosecard(int chooser, int choosee, int cardId)
{
    
}
void Client::playerDeciderevolt(bool revolt)
{
    
}
json Client::playerEndusingcard()
{
    json se ,re;
    se[str_var[0]] = 13;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    socket->SetReceived(false);
    re = json::parse(socket->GetBuffer());
    return re;
}
void Client::playerFoldcard(int amount, int *cardId)
{
    
}
void Client::endGame()
{
    
}
void Client::updateUserinfo()
{
    
}

json Client::getFriendlist()
{
    json se ,re;
    se[str_var[0]] = 17;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    re = json::parse(socket->GetBuffer());
    socket->SetReceived(false);
    return re;
}
json Client::addFriend(int friendId)
{
    json se ,re;
    se[str_var[0]] = 18;
    se["Friend ID"] = friendId;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    re = json::parse(socket->GetBuffer());
    socket->SetReceived(false);
    return re;
}
json Client::showDetermineCard(int cardId){
    json se ,re;
    se[str_var[0]] = 20;
    se["Card ID"] = cardId;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    re = json::parse(socket->GetBuffer());
    socket->SetReceived(false);
    return re;
}
json Client::userExit()
{
    json se ,re;
    se[str_var[0]] = 21;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    re = json::parse(socket->GetBuffer());
    socket->SetReceived(false);
    return re;
}

json Client::getLoungeUserInfo(){//action 22
    json se ,re;
    se[str_var[0]] = 22;
    socket->sendMessage(se.dump());
    socket->busyWaitting();
    re = json::parse(socket->GetBuffer());
    socket->SetReceived(false);
    return re;
}
