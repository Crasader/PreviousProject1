//
//  UrlDecode.hpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/10/25.
//

#ifndef UrlDecode_hpp
#define UrlDecode_hpp
#include "cocos2d.h"
USING_NS_CC;
class UrlEncode{
public:
     std::string encode(const std::string &str);
private:
     unsigned char ToHex(unsigned char x);
     unsigned char FromHex(unsigned char x);
};
#endif /* UrlDecode_hpp */
