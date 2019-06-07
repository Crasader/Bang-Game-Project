//
//  Card.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/23.
//

#ifndef Card_hpp
#define Card_hpp

#include <string>
enum class Suits{
    spades,//黑桃
    hearts,//紅心
    diamonds,//方塊
    clubs//梅花
};

class Card{
public:
    Card(){};
    Card(int id, const std::string &cardName, int suit, int number){
        card_id_ = id;
        cardName_ = cardName;
        suit_ = suit;
        number_ = number;
    }
    int get_id();
    const std::string& get_cardName() const;
    int get_suit();
    int get_number();
    const std::string& get_Description() const;
    
    void set_id(int id);
    void set_Name(std::string &name);
    void set_suit(int suit);
    void set_number(int number);
    void set_Description(std::string description);
    
private:
    int card_id_;
    std::string cardName_;
    std::string cardDescription_;
    int suit_;
    int number_;
};


class CardDatabase{
public:
    
    CardDatabase():size_(0){};
    ~CardDatabase(){
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
    
    Card* get_Card_byID(int id){
        for(auto i:data_){
            if(i->get_id() == id){
                return i;
            }
        }
        return nullptr;
    }
    Card* get_Card(int idx){
        return data_[idx];
    }
    void add_Card(Card* card){
        data_.push_back(card);
        ++size_;
    }
    void delete_Card(int idx){
        delete data_[idx];
        data_.erase(data_.begin() + idx);
        --size_;
    }
    
    static CardDatabase* getInstance(){
        if(CardDatabase::myself == nullptr){
            CardDatabase::myself = new CardDatabase();
        }
        return CardDatabase::myself;
    }
    
    
private:
    static CardDatabase *myself;
    int size_ = 0;
    std::vector<Card*> data_;
    
};
#endif /* Card_hpp */
