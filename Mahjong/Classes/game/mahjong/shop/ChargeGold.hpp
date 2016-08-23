//
//  ChargeGold.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#ifndef ChargeGold_hpp
#define ChargeGold_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class ChargeGold : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(ChargeGold);
private:
    void showChargeGold();
    void closeView();
    void chargeGoldBtn(Ref* ref);

};
#endif /* ChargeGold_hpp */
