//
//  PublicResultLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef PublicResultLayer_hpp
#define PublicResultLayer_hpp
#include "cocos2d.h"
USING_NS_CC;

class PublicResultLayer :public  Layer{
public:
    virtual bool init() override;
    CREATE_FUNC(PublicResultLayer);
private:
    void showGameResult();
    void showRoomInfo();

};
#endif /* PublicResultLayer_hpp */
