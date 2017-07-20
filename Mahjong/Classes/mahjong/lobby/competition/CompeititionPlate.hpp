//
//  CompeititionPlate.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/20.
//
//

#ifndef CompeititionPlate_hpp
#define CompeititionPlate_hpp
#include "cocos2d.h"
USING_NS_CC;

class CompeititionPlate : public Layer{
public:
    bool init();
    void onEnter();
    void onExit();
    CREATE_FUNC(CompeititionPlate);
private:
     EventListenerCustom* joinResp;
    void closeView();
};
#endif /* CompeititionPlate_hpp */
