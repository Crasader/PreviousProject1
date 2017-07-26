//
//  ShangHaiSelectLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#ifndef ShangHaiSelectLayer_hpp
#define ShangHaiSelectLayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class ShangHaiSelectLayer :public Layer{
public:
    virtual bool init();
    std::string getLeizi();
    std::string getEmsc();
    std::string getKaibao();
    CREATE_FUNC(ShangHaiSelectLayer);
private:
    void selectLeziType1();
    void selectLeziType2();
    void selectLeziType3();
    void selectLeziType4();
    void selectLeziType5();
    void selectLeziType6();
    void selectWukaibao();
    void select2mo3chong();
};


#endif /* ShangHaiSelectLayer_hpp */
