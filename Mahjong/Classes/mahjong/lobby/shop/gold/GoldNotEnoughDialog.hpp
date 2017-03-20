//
//  GoldNotEnoughDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#ifndef GoldNotEnoughDialog_hpp
#define GoldNotEnoughDialog_hpp

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class GoldNotEnoughDialog : public Layer{
public:
    static GoldNotEnoughDialog* create( EnterRoomResp newRespData,int type);
    virtual bool init( EnterRoomResp newRespData,int type);
private:
    void closeView();
    void chargeGold();
    CC_SYNTHESIZE(int , roomType, RoomType);
    int getMinGoldEnterRoom(int type);

};
#endif /* GoldNotEnoughDialog_hpp */
