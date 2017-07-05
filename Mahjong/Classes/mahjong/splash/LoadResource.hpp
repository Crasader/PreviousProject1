//
//  LoadResource.hpp
//  Mahjong
//  虚拟的资源加载界面,进度条的加载速度是固定的
//  Created by qiuzhong on 16/6/6.
//
//

#ifndef LoadResource_hpp
#define LoadResource_hpp

#include "cocos2d.h"
USING_NS_CC;

class LoadResource : public Layer{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(LoadResource);
private:
    void showHealthLayer();
    void showNormalLayer();
    void showLoadLayerAnim();
};
#endif /* LoadResource_hpp */
