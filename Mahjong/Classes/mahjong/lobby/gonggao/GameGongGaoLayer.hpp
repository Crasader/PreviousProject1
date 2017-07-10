//
//  GameGongGao.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#ifndef GameGongGao_hpp
#define GameGongGao_hpp

#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/lobby/gonggao/GongGaoItem.hpp"

USING_NS_CC;

class GameGongGaoLayer : public Layer{
public:
    static GameGongGaoLayer* create(GameGongGao gonggaoData);
    bool init(GameGongGao gonggaoData);
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
private:
    int totalPage = 4;
    int showIndex ;
    Point lastPos;
    GameGongGao myGongGao;
    std::vector<GongGaoItem*> contents;
    std::vector<Sprite*> bubbles;
    Point getBubblePos(int size,int index);
    void updateGongGao(float dt);
    void closeView();
    float getDistance(Point s, Point e);
};

#endif /* GameGongGao_hpp */
