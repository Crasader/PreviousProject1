//
//  FaceChatLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/16.
//
//

#ifndef FaceChatLayer_hpp
#define FaceChatLayer_hpp

#include "cocos2d.h"
USING_NS_CC;

class FaceChatLayer : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(FaceChatLayer);
private:
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    void faceSelected(Ref* ref);
};

#endif /* FaceChatLayer_hpp */
