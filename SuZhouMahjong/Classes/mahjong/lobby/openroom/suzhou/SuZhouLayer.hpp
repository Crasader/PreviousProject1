//
//  ShangHaiSelectLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/26.
//
//

#ifndef SuZhouLayer_hpp
#define SuZhouLayer_hpp

#include "cocos2d.h"
USING_NS_CC;


class SuZhouLayer :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(SuZhouLayer);
private:
    void showOpenRoomBtn();
    void selectDiLing();
    void selectHaoQi();
    void selectFangka8();
    void selectFangka4();
    void selectFangka16();
    void selectAA();
    void selectFZ();
    std::string getPayWay();
    std::string getHaoQi();
    std::string getDiLing();
    std::string getOpenRoomJuShu();//开设房间局数1表示8局，2表示4局，3表示16局
    void openRoom();
    void openRoomByAgency();
    void checkAgencyRecord();
};


#endif /* ShangHaiSelectLayer_hpp */
