//
//  HuaAnim.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/9.
//
//

#ifndef HuaAnim_hpp
#define HuaAnim_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#include "mahjong/common/jong/Jong.h"

class HuaAnim:public Layer{
public:
    static HuaAnim* create(std::vector<Jong*> jong,int seatId,CallFunc* func);
    virtual bool init(std::vector<Jong*> jong,int seatId,CallFunc* func);
private:
    void showHuaAnim(Sprite* sprite);
    Point getPosBySeatId(int seatId);
     Point getHuaPosBySeatId(int seatId);
};
#endif /* HuaAnim_hpp */
