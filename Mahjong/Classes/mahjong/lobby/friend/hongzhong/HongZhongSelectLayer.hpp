//
//  HongZhongSelectLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#ifndef HongZhongSelectLayer_hpp
#define HongZhongSelectLayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class HongZhongSelectLayer :public Layer{
public:
    virtual bool init();
    std::string getFanMa();
    std::string getDiFen();
    CREATE_FUNC(HongZhongSelectLayer);
private:
    void selectMa159zh();
    void selectMa159();
    void selectMa1();
    void selectDifen2();
    void selectDifen1();
    void selectDifen5();
};


#endif /* HongZhongSelectLayer_hpp */
