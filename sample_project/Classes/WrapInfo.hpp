//
//  WrapInfo.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/6/2.
//

#ifndef WrapInfo_hpp
#define WrapInfo_hpp

#include <stdio.h>
#include <stdint.h>
#include <string>
#include "nlohmann/json.hpp"
namespace WrapInfo
{
    nlohmann::json WrapRegisterUserInfo(uint32_t UID);
    nlohmann::json WrapChangeNickName(std::string);
    nlohmann::json WrapGetLoungeListInfo();
    nlohmann::json WrapJoinLounge(bool JoinMethod, uint32_t LoungeID, uint32_t UserID);
    nlohmann::json WrapSetReady(bool Ready);
    nlohmann::json WrapStartGame();
    nlohmann::json WrapChooseCharacter(const std::string & name);
    nlohmann::json WrapGetFriendListInfo();
    nlohmann::json WrapAddUser(uint32_t UID);
    nlohmann::json WrapLoungeUserInfo();
    nlohmann::json WrapPlayerUseCard(int card_id, int target);
    nlohmann::json WrapUserExit();
    nlohmann::json UserUseCard(int card_id, int target);
    nlohmann::json UserEndTurn();
}

#endif /* WrapInfo_hpp */
