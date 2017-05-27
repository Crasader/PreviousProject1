//
//  LequanShop.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#ifndef HuafeiShop_hpp
#define HuafeiShop_hpp

#include "cocos2d.h"
USING_NS_CC;

class HuafeiShop : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(HuafeiShop);
private:
    EventListenerCustom* huafeiChangeList;
    EventListenerCustom* huafeiChangeResp;
    void showHuafeiShop();
    void exchange(Ref* ref);
    void showRecord();
    void closeView();
};

#endif /* LequanShop_hpp */