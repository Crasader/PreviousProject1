//
//  ResultScene.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/17.
//
//

#ifndef ResultScene_hpp
#define ResultScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class ResultScene:public Scene{
public:
    virtual bool init() override;
    static cocos2d::Scene* createScene(int type);
private:
    void initTestData();
};

#endif /* ResultScene_hpp */
