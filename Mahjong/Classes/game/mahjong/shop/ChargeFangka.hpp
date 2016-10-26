//
//  ChargeFangka.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/26.
//
//

#ifndef ChargeFangka_hpp
#define ChargeFangka_hpp
#include "cocos2d.h"
USING_NS_CC;

class ChargeFangka :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(ChargeFangka);
private:
    void closeView();
    void confirmCharge();
};

#endif /* ChargeFangka_hpp */
