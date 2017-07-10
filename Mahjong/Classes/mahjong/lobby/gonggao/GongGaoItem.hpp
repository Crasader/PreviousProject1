//
//  GongGaoItem.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#ifndef GongGaoItem_hpp
#define GongGaoItem_hpp

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"

USING_NS_CC;

class GongGaoItem : public Layer{
public:
    static GongGaoItem* create(GameActivityData gonggaoData);
    static GongGaoItem* create(int index);
    void onEnter() override;
    void onExit() override;
    bool init(GameActivityData gonggaoData);
    bool init(int index);
private:
    Sprite* content;
    EventListenerCustom* gongGaoImgListener;
    GameActivityData myData;
    std::string getImageByIndex(int index);
};

#endif /* GongGaoItem_hpp */
