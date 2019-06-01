//
//  player.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <string>
#include <vector>

class Player{
public:
    Player(int max_hp, int hp, const std::string &charName, const std::string &PlayerName,  int position, int amount = 0){
        Max_hp_ = hp;
        hp_ = hp;
        charName_ = charName;
        PlayerName_ = PlayerName;
        position_ = position;
        holding_card_amount_ = amount;
        
    }
    
    int get_Max_hp();
    int get_hp();
    const std::string& get_charName() const;
    const std::string& get_PlayerName() const;
    int get_holding_card_amount();
    const std::vector<int>& get_holding() const;
    int get_equipment();
    int get_position();
    bool isJail();
    
    void set_Max_hp(int hp);
    void set_hp(int hp);
    void set_charName(const std::string &Name);
    void set_PlayerName(const std::string &Name);
    void set_holding_card_amount(int amount);
    bool use_card(int card);
    void add_card(int card);
    void set_position(int pos);
    void set_Jail(bool isJail);
    
private:
    int Max_hp_;
    int hp_;
    std::string PlayerName_;
    std::string charName_;
    int holding_card_amount_;
    std::vector<int> holding_;
    int equipment_;
    int position_;
    bool isJail_;
};

class PlayerDatabase{
public:
    
    PlayerDatabase():size_(0){};
    ~PlayerDatabase(){
        for(auto i:data_){
            delete i;
        }
        delete myself;
    }
    
    int get_size() const{
        return size_;
    }
    void set_size(int size){
        size_ = size;
    }
    
    Player* get_Player(int idx){
        return data_[idx];
    }
    void add_Player(Player* player){
        data_.push_back(player);
        ++size_;
    }
    void delete_Player(int idx){
        delete data_[idx];
        data_.erase(data_.begin() + idx);
    }
    
    static PlayerDatabase* getInstance(){
        if(PlayerDatabase::myself == nullptr){
            PlayerDatabase::myself = new PlayerDatabase();
        }
        return PlayerDatabase::myself;
    }
    
    
private:
    static PlayerDatabase *myself;
    int size_ = 0;
    std::vector<Player*> data_;
    
};

#endif /* player_hpp */
