//
//  DissolveItem.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/11.
//
//

#ifndef DissolveItem_hpp
#define DissolveItem_hpp

#include "cocos2d.h"
USING_NS_CC;

class DissolveItem:public Sprite{
    
public:
    static DissolveItem* create(std::string name,std::string poxiaoid);
    virtual bool init(std::string name,std::string poxiaoid);
    Sprite* state;
    void updateState(int sta);//0表示未知，1表示同意，2表示不同意
    CC_SYNTHESIZE(std::string, poxiaoId, PoxiaoId);
    CC_SYNTHESIZE(std::string, nickName, NickName);
    CC_SYNTHESIZE(int, confirm, Confirm);
};

#endif /* DissolveItem_hpp */
