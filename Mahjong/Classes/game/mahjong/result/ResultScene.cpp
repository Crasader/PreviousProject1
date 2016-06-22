//
//  ResultScene.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/17.
//
//

#include "ResultScene.hpp"
#include "ResultLayer.h"

bool ResultScene::init(){
    if (!Scene::init()){
        return false;
    }
    ResultLayer* layer = ResultLayer::create();
    this->addChild(layer);
    return true;
}
