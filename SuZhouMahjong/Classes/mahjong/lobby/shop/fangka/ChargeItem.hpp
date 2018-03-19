//
//  DiamondItem.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/13.
//
//

#ifndef ChargeItem_hpp
#define ChargeItem_hpp

#include "cocos2d.h"
USING_NS_CC;

class ChargeItem:public Sprite{
    
public:
    static ChargeItem* create(int price,int fangakNum,int payId);
    virtual bool init(int price,int fangakNum,int payId);
private:
    void confirmCharge(Ref* ref);
    CC_SYNTHESIZE(int, price, Price);
    CC_SYNTHESIZE(int, fangakNum, fangakNum);
    CC_SYNTHESIZE(int, payId, PayId);
};

#endif /* DiamondItem_hpp */
