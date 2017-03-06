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
#include "mahjong/state/GameData.h"
#include "mahjong/gonggao/GongGaoItem.hpp"

USING_NS_CC;

class GameGongGaoLayer : public Layer{
public:
    static GameGongGaoLayer* create(GameGongGao gonggaoData);
    bool init(GameGongGao gonggaoData);
private:
    int showIndex ;
    GameGongGao myGongGao;
    std::vector<GongGaoItem*> contents;
    std::vector<Sprite*> bubbles;
    Point getBubblePos(int size,int index);
    void updateGongGao(float dt);
    void closeView();
};

#endif /* GameGongGao_hpp */
