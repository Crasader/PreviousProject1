//
//  CardStack.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/1/19.
//
//

#ifndef CardStack_hpp
#define CardStack_hpp

#include "cocos2d.h"
USING_NS_CC;

class CardStack :public Node{
public:
    virtual bool init();
    CREATE_FUNC(CardStack);
    void setShowNum(int  num);
};

#endif /* CardStack_hpp */
