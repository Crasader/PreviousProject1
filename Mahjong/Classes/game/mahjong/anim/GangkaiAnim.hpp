//
//  GangkaiAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/22.
//
//

#ifndef GangkaiAnim_hpp
#define GangkaiAnim_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class GangkaiAnim : public Layer{
public:
    static GangkaiAnim* create(int seatId,bool qiang);
    virtual bool init(int seatId,bool qiang);
private:
     void showPokersLight(int seatId);
    void showCircle(int seatId,bool qiang);
    void showFlower(Sprite* sprite);
    void showLight(Sprite* sprite);
    Point getPosbySeat(int seatId);
};
#endif /* GangkaiAnim_hpp */
