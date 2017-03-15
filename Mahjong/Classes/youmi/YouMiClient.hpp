//
//  YouMiClient.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/15.
//
//

#ifndef MY_YouMiClient_hpp
#define MY_YouMiClient_hpp
#include "YIM.h"

class YouMiClient{
public:
    static YouMiClient* getInstance();
    YIMManager* getYouMiManager();
private:
    static YouMiClient* instance;
    YouMiClient(){};

};
#endif /* YouMiClient_hpp */
