//
//  ToastCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/30.
//
//

#ifndef ToastCell_hpp
#define ToastCell_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ToastCell:public Sprite{
    
public:
    static ToastCell* create(std::string msg);
    virtual bool init(std::string msg);
};


#endif /* ToastCell_hpp */
