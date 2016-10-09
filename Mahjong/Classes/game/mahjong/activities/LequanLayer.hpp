//
//  LequanLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#ifndef LequanLayer_hpp
#define LequanLayer_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class LequanLayer : public Layer{
public:
    bool virtual init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(LequanLayer);
private:
    void drawLayerUi();
    void doFunction1();
    void doFunction2();
    void doFunction3();
};

#endif /* LequanLayer_hpp */
