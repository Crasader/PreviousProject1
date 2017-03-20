//
//  RoomFullDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/26.
//
//

#ifndef RoomFullDialog_hpp
#define RoomFullDialog_hpp

#include "cocos2d.h"
USING_NS_CC;

class RoomFullDialog :public Layer{
public:
    virtual bool init();
    CREATE_FUNC(RoomFullDialog);
private:
    void closeView();
};

#endif /* RoomFullDialog_hpp */
