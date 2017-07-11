//
//  DissovleRoomDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/10.
//
//

#ifndef DissovleRoomDialog_hpp
#define DissovleRoomDialog_hpp
#include "cocos2d.h"
#include "mahjong/common/dialog/dissolve/DissolveItem.hpp"
USING_NS_CC;

class DissovleRoomDialog : public Layer{
public :
    bool init();
    CREATE_FUNC(DissovleRoomDialog);
private:
    int residueTime = 100;
    void doAgree();
    void doNotAgree();
    std::vector<DissolveItem*> items;
};

#endif /* DissovleRoomDialog_hpp */
