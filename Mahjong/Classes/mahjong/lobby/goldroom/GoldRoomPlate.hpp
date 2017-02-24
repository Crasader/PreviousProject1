//
//  GoldRoomPlate.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/25.
//
//

#ifndef GoldRoomPlate_hpp
#define GoldRoomPlate_hpp
#include "cocos2d.h"
#include "mahjong/lobby/goldroom/GoldRoomButton.hpp"
#include "mahjong/state/DataStruct.h"
USING_NS_CC;

class GoldRoomPlate : public Layer{
public:
    static GoldRoomPlate* create(RoomListData* data);
    virtual bool init(RoomListData* data);
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;

};
#endif /* GoldRoomPlate_hpp */
