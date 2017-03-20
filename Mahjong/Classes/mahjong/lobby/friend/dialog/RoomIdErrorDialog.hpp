//
//  RoomIdErrorDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/26.
//
//

#ifndef RoomIdErrorDialog_hpp
#define RoomIdErrorDialog_hpp

#include "cocos2d.h"
USING_NS_CC;

class RoomIdErrorDialog :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(RoomIdErrorDialog);
private:
    void closeView();
};

#endif /* RoomIdErrorDialog_hpp */
