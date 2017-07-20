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
    CREATE_FUNC(CompeititionPlate);
private:
    void closeView();
};
#endif /* CompeititionPlate_hpp */
