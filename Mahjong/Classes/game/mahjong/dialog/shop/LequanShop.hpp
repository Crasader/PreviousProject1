//
//  LequanShop.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#ifndef LequanShop_hpp
#define LequanShop_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class LequanShop : public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(LequanShop);
private:
    EventListenerCustom* lequanChangeList;
    void showLequanShop();
    void exchange(Ref* ref);
    void showRecord();
    void closeView();
};

#endif /* LequanShop_hpp */
