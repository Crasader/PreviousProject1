//
//  HongZhongSelectLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#ifndef HongZhongLayer_hpp
#define HongZhongLayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class HongZhongLayer :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(HongZhongLayer);
private:
    void showOpenRoomBtn();
    void selectMa159zh();
    void selectMa159();
    void selectMa1();
    void selectDifen2();
    void selectDifen1();
    void selectDifen5();
    void selectFangka8();
    void selectFangka4();
    void selectFangka16();
    void selectAA();
    void selectFZ();
    std::string getPayWay();
    std::string getFanMa();
    std::string getDiFen();
    std::string getOpenRoomJuShu();//开设房间局数1表示8局，2表示4局，3表示16局
    void openRoom();
    void openRoomByAgency();
    void checkAgencyRecord();
};


#endif /* HongZhongSelectLayer_hpp */
