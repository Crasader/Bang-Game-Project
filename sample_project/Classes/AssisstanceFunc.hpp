//
//  AssisstanceFunc.hpp
//  HelloCpp-mobile
//
//  Created by Guan Ying Chen on 2019/5/1.
//

#ifndef AssisstanceFunc_hpp
#define AssisstanceFunc_hpp

#include <stdio.h>
#include <string>

class UidHash{
public:
    static unsigned int BKDRHash(const char* input);
    static unsigned int BKDRHash(const std::string &input);
    
private:
    // Set input max length 40
    static constexpr size_t maxLength = 40;
    // Set the seed
    static constexpr unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
};

#endif /* AssisstanceFunc_hpp */
