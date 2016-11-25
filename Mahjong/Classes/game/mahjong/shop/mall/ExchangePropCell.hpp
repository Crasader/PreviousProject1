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
    static ExchangePropCell* create(int propId,int lequanNum,std::string propName,std::string url,std::string propType);
    virtual bool init(int propId,int lequanNum,std::string propName,std::string url,std::string propType);
    void onEnter() override;
    void onExit() override;
private:
    EventListenerCustom* shopPropListener;
    std::string getImageNameById(int id);
    void confirmChange(Ref* ref);
    CC_SYNTHESIZE(int, lequanNum, LequanNum);
    CC_SYNTHESIZE(std::string, propType, PropType);
    CC_SYNTHESIZE(std::string, propUrl, PropUrl);
};
#endif /* ExchangePropCell_hpp */
