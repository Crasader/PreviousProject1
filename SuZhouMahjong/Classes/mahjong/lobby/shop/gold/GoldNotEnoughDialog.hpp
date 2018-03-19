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
    static GoldNotEnoughDialog* create(EnterRoomResp newRespData);
    virtual bool init( EnterRoomResp newRespData);
private:
    void closeView();
    void chargeGold();

};
#endif /* GoldNotEnoughDialog_hpp */
