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
#include "GameScene.hpp"
#include "ChooseCardScene.hpp"

#include <thread>
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


void Client::HandleAction(const string Message)
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
            
            json cpContent = Content;
            int p_amount = static_cast<int>(cpContent["Player"].size());
            auto pdb = PlayerDatabase::getInstance();
            //"Player Name" : string,
            //"Position" : int(32-bit), (start from 0)
            for(int i=0; i<p_amount; i++){
                //Player(int max_hp, int hp, const std::string &charName, const std::string &PlayerName,  int position, int amount = 0)
                pdb->add_Player(new Player(cpContent["Player"][i]["Player Name"], cpContent["Player"][i]["Position"]));
            }
            
            int  c_amount = cpContent["Card"].size();
            auto cdb = CardDatabase::getInstance();
            //cdb->set_size(c_amount);
            
            for(int i=0; i<c_amount; i++){
                //Card(int id, std::string &cardName, int suit, int number)
                cdb->add_Card(new Card(cpContent["Card"][i]["ID"], cpContent["Card"][i]["Name"], cpContent["Card"][i]["Suit"], cpContent["Card"][i]["Number"]));
                
            }
            
            
        
            break;
        }
        case 6:
        {
            ChooseCharacterScene::SetCharacterName(Content["Character Name 0"], Content["Character Name 1"]);
            break;
        }
        case 7:
        {
            
            auto pdb = PlayerDatabase::getInstance();
            auto mine = pdb->get_Mine();

            mine->set_Max_hp(Content["Max HP"]);
            mine->set_hp(Content["HP"]);
            mine->set_team(Content["Team"]);
            mine->set_position(Content["Position"]);
            mine->set_charName(Content["Character Name"]);
            mine->set_death(Content["Death"]);
            mine->set_attack_range(Content["Attack Range"]);
            mine->set_add_range(Content["Add Range"]);
            mine->set_minus_range(Content["Minus Range"]);
            mine->set_multi_attack(Content["Multi Attack"]);
            
            auto &HoldingVec = mine->get_holding();
            HoldingVec.clear();
            
            for(int i=0; i<Content["Holding"].size(); i++){
                HoldingVec.push_back(Content["Holding"][i]["Card ID"]);
                std::cout<<"push_back "<<Content["Holding"][i]["Card ID"]<<std::endl;
            }
            
            //mine->set_holding_card_amount(HoldingVec.size());
            mine->set_equipment(Content["Equipment"]);
            
            pdb->delete_Player_by_pos(mine->get_position());
            
            //-------------------------------------------------
            for(int i=0; i<Content["Player"].size(); i++){
                int tPos = Content["Player"][i]["Position"];
                Player* player;
                if(tPos != pdb->get_Mine()->get_position()){
                    player = pdb->get_Player_byPos(tPos);
                }
                else{
                    player = pdb->get_Mine();
                }
                
                player->set_Max_hp(Content["Player"][i]["Max HP"]);
                player->set_hp(Content["Player"][i]["HP"]);
                player->set_charName(Content["Player"][i]["Character Name"]);
                player->set_death(Content["Player"][i]["Death"]);
                if(Content["Player"][i].find("Team") != Content["Player"][i].end()){
                    player->set_team(Content["Player"][i]["Team"]);
                }
                player->set_position(Content["Player"][i]["Position"]);
                player->set_attack_range(Content["Player"][i]["Attack Range"]);
                player->set_add_range(Content["Player"][i]["Add Range"]);
                player->set_minus_range(Content["Player"][i]["Minus Range"]);
                player->set_multi_attack(Content["Player"][i]["Multi Attack"]);
                //player->set_holding_card_amount(Content["Player"][i]["Holding Card Amount"]);
                player->set_equipment(Content["Player"][i]["Equipment"]);
            }
            
            break;
        }
        case 8:
        {
            //It is my turn;
            break;
        }
        case 9:{
            //player use card
            //update player info
            
            auto pdb = PlayerDatabase::getInstance();
            auto mine = pdb->get_Mine();
 
            mine->set_Max_hp(Content["Max HP"]);
            mine->set_hp(Content["HP"]);
            mine->set_team(Content["Team"]);
            mine->set_position(Content["Position"]);
            mine->set_charName(Content["Character Name"]);
            mine->set_death(Content["Death"]);
            mine->set_attack_range(Content["Attack Range"]);
            mine->set_add_range(Content["Add Range"]);
            mine->set_minus_range(Content["Minus Range"]);
            mine->set_multi_attack(Content["Multi Attack"]);
            
            auto &HoldingVec = mine->get_holding();
            HoldingVec.clear();
            
            for(int i=0; i<Content["Holding"].size(); i++){
                HoldingVec.push_back(Content["Holding"][i]["Card ID"]);
                std::cout<<"push_back "<<Content["Holding"][i]["Card ID"]<<std::endl;
            }
           
            mine->set_equipment(Content["Equipment"]);
            
            //-------------------------------------------------
            for(int i=0; i<Content["Player"].size(); i++){
                int tPos = Content["Player"][i]["Position"];
                Player* player;
                if(tPos != pdb->get_Mine()->get_position()){
                    player = pdb->get_Player_byPos(tPos);
                }
                else{
                    player = pdb->get_Mine();
                }
                
                player->set_Max_hp(Content["Player"][i]["Max HP"]);
                player->set_hp(Content["Player"][i]["HP"]);
                player->set_charName(Content["Player"][i]["Character Name"]);
                player->set_death(Content["Player"][i]["Death"]);
                if(Content["Player"][i].find("Team") != Content["Player"][i].end()){
                    player->set_team(Content["Player"][i]["Team"]);
                }
                player->set_position(Content["Player"][i]["Position"]);
                player->set_attack_range(Content["Player"][i]["Attack Range"]);
                player->set_add_range(Content["Player"][i]["Add Range"]);
                player->set_minus_range(Content["Player"][i]["Minus Range"]);
                player->set_multi_attack(Content["Player"][i]["Multi Attack"]);
                //player->set_holding_card_amount(Content["Player"][i]["Holding Card Amount"]);
                player->set_equipment(Content["Player"][i]["Equipment"]);
            }
            break;
        }
        case 10:
        {
            //Player show card to another;
            /*
             "Shower Position" : int,
             "Showee Position" : int,
             "Card" :
             [
             {
             "ID" : int(32-bit)
             },
             ...
             ]
             */
            int shower_pos = Content["Shower Position"];
            int showee_pos = Content["Showee Position"];
            int show_amount = Content["Card"].size();
            for(int i=0; i<show_amount; i++){
                //need write something
                //...
            }
            
            break;
        }
        case 11:{
            
            
            auto gs = cocos2d::Director::getInstance()->getRunningScene();
            auto ChooseL = static_cast<ChooseCardLayer*>(gs->getChildByTag(2)); // Choose card Layer
            
            if(Content["Chooser Position"] != PlayerDatabase::getInstance()->get_Mine()->get_position()){
                break;
            }
            
            ChooseL->chooser_ = Content["Chooser Position"];
            ChooseL->choosee_ = Content["Choosee Position"];
            ChooseL->set_ChooseOrDiscard(Content["Choose or Discard"]);
            
            int card_amount = Content["Card"].size();
            
            auto &cardList = ChooseL->cardList_;
            
            cardList.clear();
            
            for(int i=0; i<card_amount; i++){
                cardList.push_back(Content["Card"][i]["ID"]);
            }
            
            break;
        }
        case 16:
        {
            auto user = User::getInstance();
            user->setNickName(Content["Nick Name"]);
            user->setMoney(Content["User Money"]);
            user->setWin(Content["User Win"]);
            user->setLose(Content["User Lose"]);
            
            break;
        }
        case 17:
        {
            int FriendSize = static_cast<int>(Content["Friend"].size());
            
            //Friend 0, Friend 1 ....
            FriendDatabase::getInstance()->clear();
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
            static_cast<FriendScene*>(cocos2d::Director::getInstance()->getRunningScene())->setSearch_state(State);
            //FriendScene::getInstance()->setSearch_state(State);
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
        default:
            break;
    }
    
    CClientSocket::getInstance()->SetHandledAction(Action);
    
   
    GameScene::set_action(Action);

}





void Client::playerChoosecharacter(const string &charname)
{
    json se;
    se[str_var[0]] = 6;
    se["Choose Character Name"] = charname;
    socket->sendMessage(se.dump());
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
