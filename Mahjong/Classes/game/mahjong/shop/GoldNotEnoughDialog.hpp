//
//  GoldNotEnoughDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#ifndef GoldNotEnoughDialog_hpp
#define GoldNotEnoughDialog_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class GoldNotEnoughDialog : public Layer{
public:
    static GoldNotEnoughDialog* create(int type);
    virtual bool init(int type);
private:
    void closeView();
    void chargeGold();
    CC_SYNTHESIZE(int , roomType, RoomType);
    int getMinGoldEnterRoom(int type);

};
#endif /* GoldNotEnoughDialog_hpp */
