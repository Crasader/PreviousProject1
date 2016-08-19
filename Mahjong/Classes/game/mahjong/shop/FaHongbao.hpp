//
//  FaHongbao.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#ifndef FaHongbao_hpp
#define FaHongbao_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class FaHongbao : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(FaHongbao);
private:
    void showFaHongbao();
    void closeView();

};
#endif /* FaHongbao_hpp */
