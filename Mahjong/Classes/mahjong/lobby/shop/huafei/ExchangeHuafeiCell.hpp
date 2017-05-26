//
//  ExchangePropCell.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#ifndef ExchangeHuafeiCell_hpp
#define ExchangeHuafeiCell_hpp

#include "cocos2d.h"
USING_NS_CC;

class ExchangeHuafeiCell:public Sprite{

public:
    static ExchangeHuafeiCell* create(std::string propId,std::string url,std::string price,std::string name);
    virtual bool init(std::string propId,std::string url,std::string price,std::string name);
    void onEnter() override;
    void onExit() override;
private:
    EventListenerCustom* shopPropListener;
    std::string getImageNameById(int id);
    void confirmChange(Ref* ref);
    CC_SYNTHESIZE(std::string, propUrl, PropUrl);
    CC_SYNTHESIZE(std::string, propName, propName);
    CC_SYNTHESIZE(std::string, propPrice, propPrice);
};
#endif /* ExchangePropCell_hpp */
