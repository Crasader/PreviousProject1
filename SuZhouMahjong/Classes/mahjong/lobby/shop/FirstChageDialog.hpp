//
//  FirstChageDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#ifndef FirstChageDialog_hpp
#define FirstChageDialog_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class FirstChargeDialog:public Layer{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(FirstChargeDialog);
private:
    EventListenerCustom* firstChargeInfo;
    void showFirstCharge();
    void closeView();
    void charge();
};
#endif /* FirstChageDialog_hpp */
