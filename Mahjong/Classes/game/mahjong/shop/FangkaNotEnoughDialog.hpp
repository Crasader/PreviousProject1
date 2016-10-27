//
//  ChargeFangka.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/26.
//
//

#ifndef FangkaNotEnoughDialog_hpp
#define FangkaNotEnoughDialog_hpp
#include "cocos2d.h"
USING_NS_CC;

class FangkaNotEnoughDialog :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(FangkaNotEnoughDialog);
private:
    void closeView();
    void confirmCharge();
};

#endif /* ChargeFangka_hpp */
