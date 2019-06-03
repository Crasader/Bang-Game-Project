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
    Player(){};
    Player(const std::string &PlayerName,  int position){
        PlayerName_ = PlayerName;
        position_ = position;
        
    }
    Player(int max_hp, int hp, int team, const std::string &PlayerName ,const std::string &charName,   int position, int amount = 0){
        Max_hp_ = hp;
        hp_ = hp;
        team_ = team;
        PlayerName_ = PlayerName;
        charName_ = charName;
        position_ = position;
        holding_card_amount_ = amount;
    }
    Player(int max_hp, int hp, int team, const std::string &charName,   int position, int amount = 0){
        Max_hp_ = hp;
        hp_ = hp;
        team_ = team;
        charName_ = charName;
        position_ = position;
        holding_card_amount_ = amount;
    }
    
    int get_Max_hp() const;
    int get_hp() const;
    int get_team() const;
    bool is_death() const;
    int get_add_range() const;
    int get_minus_range() const;
    bool is_multi_attack() const;
    int get_attack_range() const{
        return attack_range_;
    }
    
    
    const std::string& get_charName() const;
    const std::string& get_PlayerName() const;
    int get_holding_card_amount() const;
    std::vector<int>& get_holding();
    int get_equipment() const;
    int get_position() const;
    bool isJail() const;
    
    void set_Max_hp(int hp);
    void set_hp(int hp);
    
    void set_team(int team) ;
    void set_death(bool is_death) ;
    void set_add_range(int range) ;
    void set_minus_range(int range) ;
    void set_multi_attack(bool multi_attack) ;
    
    void set_charName(const std::string &Name);
    void set_PlayerName(const std::string &Name);
    void set_holding_card_amount(int amount);
    void set_equipment(int equ){
        equipment_ = equ;
    }
    bool use_card(int card);
    void add_card(int card);
    void set_position(int pos);
    void set_Jail(bool isJail);
    void set_attack_range(int range){
        attack_range_ = range;
    }
    
private:
    int Max_hp_ = 0;
    int hp_ = 0;
    int team_ = -1;
    /*
     Sergeant = 0, //警長
     ChiefSergeant = 1, //副警長
     BadAss = 2, //歹徒
     Traitor = 3 //叛徒
    */
    std::string PlayerName_;
    std::string charName_;
    bool death_ = false;
    int attack_range_ = 1;
    int add_range_ = 0;
    int minus_range_ = 0;
    bool multi_attack_ = false;
    
    int holding_card_amount_ = 0;
    std::vector<int> holding_;
    
    int equipment_  = 0xffffffff;
    int position_ = -1;
    bool isJail_ = 0;
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
    
    /*
    void set_size(int size){
        size_ = size;
    }
    */
    
    Player* get_Player(int idx){
        return data_[idx];
    }
    Player* get_Player_byPos(int pos){
        for(auto i:data_){
            if(i->get_position() == pos){
                return i;
            }
        }
    }
    
    Player* get_Mine(){
        if(mine_ == nullptr){
            mine_ = new Player();
        }
        return mine_;
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
    
    void set_Mine(int max_hp, int hp, int team, const std::string PlayerName, const std::string &charName,   int position, int amount = 0){
        if(mine_ == nullptr){
            mine_ = new Player( max_hp,  hp, team, PlayerName ,charName, position, amount = 0);
        }
        else{
            mine_->set_Max_hp(max_hp);
            mine_->set_hp(hp);
            mine_->set_team(team);
            mine_->set_PlayerName(PlayerName);
            mine_->set_charName(charName);
            mine_->set_position(position);
            mine_->set_holding_card_amount(amount);
        }
    }
private:
    static PlayerDatabase *myself;
    int size_ = 0;
    Player* mine_ = nullptr;
    std::vector<Player*> data_;
    
};

#endif /* player_hpp */
