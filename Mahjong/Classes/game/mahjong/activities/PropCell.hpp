//
//  ExchangePropCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#ifndef PropCell_hpp
#define PropCell_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class PropCell:public Sprite{

public:
    static PropCell* create(std::string propId,int rid,std::string name,std::string status);
    virtual bool init(std::string propId,int rid,std::string name,std::string status);
private:
    std::string getImageNameById(int id);
    void confirmChange(Ref* ref);
    CC_SYNTHESIZE(int, propRid, PropRid);
    CC_SYNTHESIZE(std::string, propId, PropId);
    CC_SYNTHESIZE(std::string, propName, PropName);
};
#endif /* ExchangePropCell_hpp */
