//
//  GoldRelieve.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/19.
//
//

#ifndef GoldRelieve_hpp
#define GoldRelieve_hpp
#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;
class GoldRelieve : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CC_SYNTHESIZE(int, relieveNum, RelieveNum);
    CREATE_FUNC(GoldRelieve);
private:
    void closeView();
    void chargeGold();
    void getRelieve();
};
#endif /* GoldRelieve_hpp */
