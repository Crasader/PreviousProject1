//
//  ShangHaiSelectLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#ifndef ChongMingSelectLayer_hpp
#define ChongMingSelectLayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class ChongMingSelectLayer :public Layer{
public:
    virtual bool init();
    std::string getDiHua();
    std::string getLeizi();
    std::string getKaibao();
    std::string getFeiChangYin();
    CREATE_FUNC(ChongMingSelectLayer);
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
    void selectFeiChangYin();
};


#endif /* ChongMingSelectLayer */
