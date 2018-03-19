//
//  ShangHaiSelectLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#ifndef BaiDaLayer_hpp
#define BaiDaLayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class BaiDaLayer :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(BaiDaLayer);
private:
    void showOpenRoomBtn();
    void selectZiMoHu();
    void selectQiDuiHu();
    void selectFanPaiZero();
    void selectFanPaiTwo();
    void selectFanPaiFour();
    void selectFanPaiSix();
    void selectFangka8();
    void selectFangka4();
    void selectFangka16();
    void selectAA();
    void selectFZ();
    std::string getPayWay();
    std::string getFanPai();
    std::string getOnlyZimo();
    std::string getQiDui();
    std::string getOpenRoomJuShu();//开设房间局数1表示8局，2表示4局，3表示16局
    void openRoom();
    void openRoomByAgency();
    void checkAgencyRecord();
};


#endif /* ChongMingSelectLayer */
