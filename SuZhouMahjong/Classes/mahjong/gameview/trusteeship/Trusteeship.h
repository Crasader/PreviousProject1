#ifndef __Trusteeship__H__
#define __Trusteeship__H__
#include "cocos2d.h"
USING_NS_CC;

class Trusteeship : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(Trusteeship);
private:
   void  cancle();
};
#endif
