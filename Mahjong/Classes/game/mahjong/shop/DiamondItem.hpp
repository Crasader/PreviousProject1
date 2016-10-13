//
//  DiamondItem.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/13.
//
//

#ifndef DiamondItem_hpp
#define DiamondItem_hpp

#include "cocos2d.h"
USING_NS_CC;

class DiamondItem:public Sprite{
    
public:
    static DiamondItem* create(int price,int diamond);
    virtual bool init(int price,int diamond);
private:
    void confirmCharge(Ref* ref);
    CC_SYNTHESIZE(int, price, Price);
    CC_SYNTHESIZE(int, diamondNum, DiamondNum);
};

#endif /* DiamondItem_hpp */
