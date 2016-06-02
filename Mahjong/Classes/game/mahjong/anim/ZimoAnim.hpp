//
//  ZimoAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/25.
//
//

#ifndef ZimoAnim_hpp
#define ZimoAnim_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class ZimoAnim:public Layer{
public:
    static ZimoAnim* create(int seatId);
    virtual bool init(int seatId);
    CC_SYNTHESIZE(bool, redLight, RedLight);
    CC_SYNTHESIZE(bool, greenLight, GreenLight);

private:
    void showPokersLight(int seatId);
    void showZimoAnim(int seatId);
    Point getPosbySeat(int seatId);
    void showStarligth(Sprite* sprite);
    void showColorAnim(Sprite* sprite);
    void showColorLightAnim(Sprite* sprite);
};
#endif /* ZimoAnim_hpp */
