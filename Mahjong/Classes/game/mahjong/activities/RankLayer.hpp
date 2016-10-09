//
//  RankLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#ifndef RankLayer_hpp
#define RankLayer_hpp

#include "cocos2d.h"
USING_NS_CC;

class RankLayer : public Layer{
public:
    bool virtual init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(RankLayer);
private:
    void drawLayerUi();
};
#endif /* RankLayer_hpp */
