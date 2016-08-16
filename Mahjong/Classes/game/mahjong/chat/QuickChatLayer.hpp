//
//  QuickChatLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//

#ifndef QuickChatLayer_hpp
#define QuickChatLayer_hpp
#include "cocos2d.h"
USING_NS_CC;

class QuickChatLayer : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(QuickChatLayer);
private:
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
};
#endif /* QuickChatLayer_hpp */
