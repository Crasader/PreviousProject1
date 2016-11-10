//
//  ScrollCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/10.
//
//

#ifndef ScrollCell_hpp
#define ScrollCell_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ScrollCell : public Sprite{
public:
    static ScrollCell* create(std::string msg);
    virtual bool init(std::string msg);
    void setString(std::string msg);
private:
    Label* _mLable;
};
#endif /* ScrollCell_hpp */
