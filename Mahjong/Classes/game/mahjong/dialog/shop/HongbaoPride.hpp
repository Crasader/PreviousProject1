//
//  HongbaoPride.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#ifndef HongbaoPride_hpp
#define HongbaoPride_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HongbaoPride : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(HongbaoPride);
private:
    void showHongbaoPride();
    void closeView();
    
};
#endif /* HongbaoPride_hpp */
