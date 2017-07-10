//
//  GameGongGao.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#ifndef GongZhongHaoLayer_hpp
#define GongZhongHaoLayer_hpp

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/lobby/gongzhonghao/GongZhongHaoItem.hpp"

USING_NS_CC;

class GongZhongHaoLayer : public Layer{
public:
    static GongZhongHaoLayer* create();
    bool init();
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
private:
    int totalPage = 4;
    int showIndex ;
    Point lastPos;
    std::vector<GongZhongHaoItem*> contents;
    std::vector<Sprite*> bubbles;
    Point getBubblePos(int size,int index);
    void updateGongGao(float dt);
    void closeView();
    float getDistance(Point s, Point e);
};

#endif /* GameGongGao_hpp */
