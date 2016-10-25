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
USING_NS_CC;

class GoldRoomPlate : public Layer{
public:
    virtual bool init();
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    CREATE_FUNC(GoldRoomPlate);
private:
    void openRoomOne();
    void openRoomTwo();
    void openRoomThree();

};
#endif /* GoldRoomPlate_hpp */
