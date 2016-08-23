//
//  ChargeDiamond.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#ifndef ChargeDiamond_hpp
#define ChargeDiamond_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class ChargeDiamond:public Layer{

public :
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(ChargeDiamond);
private:
    void showChargeDialog();
    void closeView();
    void chargeButtonClick(Ref* ref);

};
#endif /* ChargeDiamond_hpp */
