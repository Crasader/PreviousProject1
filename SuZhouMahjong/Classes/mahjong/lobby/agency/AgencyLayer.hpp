//
//  AgencyLayer.hpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/22.
//

#ifndef AgencyLayer_hpp
#define AgencyLayer_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mahjong/lobby/agency/AgencyRoom.hpp"
#include "mahjong/lobby/agency/AgencyRecord.hpp"
USING_NS_CC;
USING_NS_CC_EXT;

class AgencyLayer : public Layer{
public:
    bool init() override;
    CREATE_FUNC(AgencyLayer);
     void updateData();
private:
    AgencyRoom* roomLayer;
    AgencyRecord* recordLayer;
    void closeView();
    void showYiKai();
    void showJiLu();
    void showAgencyBill();
};
#endif /* AgencyLayer_hpp */
