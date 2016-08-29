//
//  GoldNotEnoughDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#ifndef DiamondNotEnoughDialog_hpp
#define DiamondNotEnoughDialog_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class DiamondNotEnoughDialog : public Layer{
public:
    static DiamondNotEnoughDialog* create();
    virtual bool init();
private:
    void closeView();
    void chargeDiamond();

};
#endif /* GoldNotEnoughDialog_hpp */
