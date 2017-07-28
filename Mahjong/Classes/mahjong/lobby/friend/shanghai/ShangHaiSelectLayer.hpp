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
    std::string getDiHua();
    std::string getLeizi();
    std::string getEmsc();
    std::string getKaibao();
    std::string getFeiChangYin();
    CREATE_FUNC(ShangHaiSelectLayer);
private:
    void selectDiHua11();
    void selectDiHua22();
    void selectDiHua62();
    void selectDiHua55();
    void selectLezi20();
    void selectLezi50();
    void selectLezi100();
    void selectLeziWu();
    void selectWukaibao();
    void select2mo3chong();
    void selectFeiChangYin();
};


#endif /* ShangHaiSelectLayer_hpp */
