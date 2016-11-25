//
//  ExchangePropCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#ifndef ExchangePropCell_hpp
#define ExchangePropCell_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class ExchangePropCell:public Sprite{

public:
    static ExchangePropCell* create(int propId,int lequanNum,std::string propName,std::string url);
    virtual bool init(int propId,int lequanNum,std::string propName,std::string url);
private:
    std::string getImageNameById(int id);
    void confirmChange(Ref* ref);
    CC_SYNTHESIZE(int, lequanNum, LequanNum);
};
#endif /* ExchangePropCell_hpp */
