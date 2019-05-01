//
//  AssisstanceFunc.cpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/1.
//

#include "AssisstanceFunc.hpp"




unsigned int UidHash::BKDRHash(const char* input){
    char cstr[maxLength];
    strncpy(cstr, input, maxLength);

    unsigned int hash = 0;
    
    char *str = cstr;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    
    return (hash & 0x7FFFFFFF);
    
}

unsigned int UidHash::BKDRHash(const std::string& input){
    char cstr[maxLength];
    strncpy(cstr, input.c_str(), maxLength);
    
    unsigned int hash = 0;
    
    char *str = cstr;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    
    return (hash & 0x7FFFFFFF);
}
