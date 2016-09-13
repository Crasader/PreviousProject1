//
//  LoadResource.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/6.
//
//

#ifndef LoadResource_hpp
#define LoadResource_hpp

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;

class LoadResource : public Layer{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(LoadResource);
private:
    void showHealthLayer();
    void showLayer();
};
#endif /* LoadResource_hpp */
