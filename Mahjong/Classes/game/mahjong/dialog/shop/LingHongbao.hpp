//
//  LingHongbao.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#ifndef LingHongbao_hpp
#define LingHongbao_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class LingHongbao : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(LingHongbao);
private:
    void showLingHongbao();
    void closeView();
    
};
#endif /* LingHongbao_hpp */
