//
//  GongGaoItem.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#ifndef GongZhongHaoItem_hpp
#define GongZhongHaoItem_hpp

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"

USING_NS_CC;

class GongZhongHaoItem : public Layer{
public:
    static GongZhongHaoItem* create(int index);
    bool init(int index);
private:
    std::string getImageByIndex(int index);
};

#endif /* GongZhongHaoItem */
