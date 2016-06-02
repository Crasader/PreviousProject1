//
//  ResultScene.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/17.
//
//

#include "game/mahjong/result/ResultScene.hpp"
#include "game/mahjong/result/ResultLayer.h"

bool ResultScene::init(){
    if (!Scene::init()){
        return false;
    }
    ResultLayer* layer = ResultLayer::create();
    this->addChild(layer);
    return true;
}
