//
//  PrideLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#ifndef PrideLayer_hpp
#define PrideLayer_hpp

#include "cocos2d.h"
USING_NS_CC;

class PrideLayer : public Layer{
public:
    bool virtual init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(PrideLayer);
private:
    void drawLayerUi();
};

#endif /* PrideLayer_hpp */
