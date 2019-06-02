//
//  NetworkCom.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/24.
//

#include "NetworkCom.hpp"
#include "User.hpp"
#include "LobbyScene.hpp"
#include "FriendScene.hpp"
#include "ChooseCharacterScene.hpp"
#include "player.hpp"
#include "Card.hpp"
#include "LoungeScene.hpp"

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
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
        //socket = new CClientSocket(28716, "104.199.215.104");
        socket = CClientSocket::getInstance();
    }
}
Client::~Client()
{
    delete socket;
}


void Client::HandleAction(const string & Message)
{
    json Content = json::parse(Message);
    int Action = Content["Action"];
    auto client = Client::getInstance();
    auto user = User::getInstance();
    
    switch(Action)
    {
        case 0:
        {
            user->setMoney(Content["User Money"]);
            user->setNickName(Content["Nick Name"]);
            user->setWin(Content["User Win"]);
            user->setLose(Content["User Lose"]);
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            int loungSize = static_cast<int>(Content["Lounge"].size());
            LoungeDatabase::getInstance()->clear();
            
            
            //Lounge 0, Loung 1 ....
            
            std::string sLounge = "Lounge";
            
            for(int i=0;  i<loungSize; i++){
                
                unsigned int tID = Content[sLounge][i]["ID"];
                int tAmount = Content[sLounge][i]["User Amount"];
                
                LoungeDatabase::getInstance()->add_Lounge(new LoungeInfo(tID, tAmount));
            }
            break;
        }
        case 3:
        {
            break;
        }
        case 5:
        {
            int p_amount = static_cast<int>(Content["Player"].size());
            auto pdb = PlayerDatabase::getInstance();
            pdb->set_size(p_amount);
            //"Player Name" : string,
            //"Position" : int(32-bit), (start from 0)
            for(int i=0; i<p_amount; i++){
                //Player(int max_hp, int hp, const std::string &charName, const std::string &PlayerName,  int position, int amount = 0)
                pdb->add_Player(new Player(0, 0, "", Content["Player"][i]["Player Name"], Content["Player"][i]["Position"], 0));
            }
            
            int  c_amount = Content["Card"].size();
            auto cdb = CardDatabase::getInstance();
            cdb->set_size(c_amount);
            /*
             "Name" : string,
             "ID" : int(32-bit)
             "Suit" : 0 or 1 or 2 or 3,
             "Number" : 1~13
             */
            for(int i=0; i<c_amount; i++){
                //Card(int id, std::string &cardName, int suit, int number)
                cdb->add_Card(new Card(Content["Card"][i]["ID"], Content["Card"][i]["Name"], Content["Card"][i]["Suit"], Content["Card"][i]["Number"]));
                
            }
            
           
            
            
            
            break;
        }
        case 6:
        {
            ChooseCharacterScene::SetCharacterName(Content["Character Name 0"], Content["Character Name 1"]);
            /*
            auto dir = cocos2d::Director::getInstance();
            auto Rscene = ChooseCharacterScene::createScene();
            dir->replaceScene(Rscene);
            */
            break;
        }
        case 17:
        {
            int FriendSize = static_cast<int>(Content["Friend"].size());
            FriendDatabase::getInstance()->set_size(FriendSize);
            
            //CCLOG(rec.dump().c_str());
            //Friend 0, Friend 1 ....
            
            std::string sFriend = "Friend";
            
            for(int i=0;  i<FriendSize; i++){
                
                unsigned int tID = Content[sFriend][i]["Friend ID"];
                
                FriendDatabase::getInstance()->add_friend(new FriendInfo(tID, true));
                
            }
            break;
        }
        case 18:
        {
            int State = Content["Result"];
            FriendScene::getInstance()->setSearch_state(State);
            break;
        }
        case 22:
        {
            int UserSize = static_cast<int>(Content["User"].size());
            LoungeUserDatabase::getInstance()->clear();
            
            
            //CCLOG(rec.dump().c_str());
            //Lounge 0, Loung 1 ....
            
            std::string sUser = "User";
            
            for(int i=0;  i<UserSize; i++){
                
                unsigned int tID = Content[sUser][i]["ID"];
                bool isready = Content[sUser][i]["Ready"];
                
                LoungeUserDatabase::getInstance()->add_User(new LoungeUserInfo(tID, isready));
            }

            break;
        }
    }
    CClientSocket::getInstance()->SetHandledAction(Action);
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
/*
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
*/
