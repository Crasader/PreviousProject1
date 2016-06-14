//
//  LequanExchangeRecord.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/14.
//
//

#ifndef LequanExchangeRecord_hpp
#define LequanExchangeRecord_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class LequanExchangeRecord : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(LequanExchangeRecord);
private:
    void showLequanExchangeRecord();
    void closeView();
};
#endif /* LequanExchangeRecord_hpp */
