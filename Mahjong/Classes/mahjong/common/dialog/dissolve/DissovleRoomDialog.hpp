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
    void onEnter();
    void onExit();
    CREATE_FUNC(DissovleRoomDialog);
private:
    void update(float dt);
    EventListenerCustom* dissovleListener;
    MenuItemImage* img1;
    MenuItemImage* img2;
    int residueTime = 100;
    void doAgree();
    void doNotAgree();
    void checkAllConfirm();
    std::vector<DissolveItem*> items;
};

#endif /* DissovleRoomDialog_hpp */
