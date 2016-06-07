//
//  EnterRoomDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#ifndef EnterRoomDialog_hpp
#define EnterRoomDialog_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

enum EnterRoomDialogType{
    goldNotEnough,
    goldMoreLeve1,
    goldMoreLeve2
};

class EnterRoomDialog : public Layer{
public:
    static EnterRoomDialog* create(EnterRoomDialogType goldLess);
    virtual bool init(EnterRoomDialogType goldLess);
private:
    void closeView();
};
#endif /* EnterRoomDialog_hpp */
