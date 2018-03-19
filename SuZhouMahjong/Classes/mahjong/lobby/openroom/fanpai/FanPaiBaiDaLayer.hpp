//
//  ShangHaiSelectLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#ifndef FanPaiBaiDaLayer_hpp
#define FanPaiBaiDaLayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class FanPaiBaiDaLayer :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(FanPaiBaiDaLayer);
private:
    void showOpenRoomBtn();
    void selectYou();
    void selectWu();
    void selectDifen1();
    void selectDifen5();
    void selectDifen10();
    void selectFangka8();
    void selectFangka4();
    void selectFangka16();
    void selectAA();
    void selectFZ();
    std::string getPayWay();
    std::string getOpenRoomJuShu();//开设房间局数1表示8局，2表示4局，3表示16局
    std::string getDiFen();
    std::string getMengQing();
    void openRoom();
    void openRoomByAgency();
    void checkAgencyRecord();
};


#endif /* ChongMingSelectLayer */
