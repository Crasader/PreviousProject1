//
//  ResultScene.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/17.
//
//

#include "game/mahjong/result/ResultScene.hpp"
#include "game/mahjong/result/ResultLayer.h"
#include "game/mahjong/result/PublicResultLayer.hpp"

bool ResultScene::init(){
    if (!Scene::init()){
        return false;
    }
    PublicResultLayer* layer = PublicResultLayer::create();
    addChild(layer);
    return true;
}
