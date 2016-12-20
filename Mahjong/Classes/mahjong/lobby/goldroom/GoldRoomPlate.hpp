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
USING_NS_CC;

class GoldRoomPlate : public Layer{
public:
    virtual bool init() override;
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    CREATE_FUNC(GoldRoomPlate);

};
#endif /* GoldRoomPlate_hpp */
