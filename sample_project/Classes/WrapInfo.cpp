//
//  WrapInfo.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/2.
//

#include "WrapInfo.hpp"
#include <stdint.h>
using namespace nlohmann;
json WrapInfo::WrapRegisterUserInfo(uint32_t UID)
{
    json Buffer;
    Buffer["Action"] = 0;
    Buffer["User ID"] = UID;
    return Buffer;
}
json WrapInfo::WrapChangeNickName(std::string nickname)
{
    json Buffer;
    Buffer["Action"] = 1;
    Buffer["Nick Name"] = nickname;
    return Buffer;
}
json WrapInfo::WrapGetLoungeListInfo()
{
    json Buffer;
    Buffer["Action"] = 2;
    return Buffer;
}
json WrapInfo::WrapJoinLounge(bool JoinMethod, uint32_t LoungeID, uint32_t UserID)
{
    json Buffer;
    Buffer["Action"] = 3;
    Buffer["Join Method"] = JoinMethod;
    Buffer["Lounge ID"] = LoungeID;
    Buffer["User ID"] = UserID;
    return Buffer;
}
json WrapInfo::WrapSetReady(bool Ready)
{
    json Buffer;
    Buffer["Action"] = 4;
    Buffer["Ready"] = Ready;
    return Buffer;
}
json WrapInfo::WrapStartGame()
{
    json Buffer;
    Buffer["Action"] = 5;
    return Buffer;
}
json WrapInfo::WrapChooseCharacter(const std::string & name)
{
    json Buffer;
    Buffer["Action"] = 6;
    Buffer["Choose Character Name"] = name;
    return Buffer;
}

json WrapInfo::WrapGetFriendListInfo()
{
    json Buffer;
    Buffer["Action"] = 17;
    return Buffer;
}
json WrapInfo::WrapAddUser(uint32_t UID)
{
    json Buffer;
    Buffer["Action"] = 18;
    Buffer["Friend ID"] = UID;
    return Buffer;
}
json WrapInfo::WrapLoungeUserInfo()
{
    json Buffer;
    Buffer["Action"] = 22;
    return Buffer;
}

json WrapPlayerUseCard(int card_id, int target){
    json Buffer;
    Buffer["Action"] = 9;
    Buffer["Card ID"] = card_id;
    Buffer["Target Position"] = target;
    return Buffer;
}
json WrapUserExit(){
    json Buffer;
    Buffer["Action"] = 21;
    return Buffer;
}
json UserUseCard(int card_id, int target){
    json Buffer;
    Buffer["Action"] = 9;
    Buffer["Card ID"] = card_id;
    Buffer["Target Position"] = target;
    
    return Buffer;
}
json UserEndTurn(){
    json Buffer;
    Buffer["Action"] = 13;
    return Buffer;
}
