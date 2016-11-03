//
//  NumberKeypads.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/17.
//
//

#ifndef MahjongNumberKeypads_hpp
#define MahjongNumberKeypads_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MahjongNumberKeypads : public Layer{
public:
    virtual bool init();
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    CREATE_FUNC(MahjongNumberKeypads);
private:
    void clickNumber(Ref* ref);
    Label* numberShow;
    std::string enterRoomNumber;
    void closeView();
};
#endif /* NumberKeypads_hpp */
