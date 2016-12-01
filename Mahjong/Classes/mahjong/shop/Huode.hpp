//
//  Huode.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/26.
//
//

#ifndef Huode_hpp
#define Huode_hpp

#include "cocos2d.h"
USING_NS_CC;

class Huode : public Layer{
public:
    static Huode* create(int gold,int diamond,int lequan);
    virtual bool init(int gold,int diamond,int lequan);
private:
    void confirm();
};
#endif /* Huode_hpp */
