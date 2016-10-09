//
//  PrideLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#include "game/mahjong/activities/PrideLayer.hpp"
#include "game/mahjong/shop/ExchangePropCell.hpp"


bool PrideLayer::init(){
    if(!Layer::init()){
        return false;
    }
    drawLayerUi();
    return true;
}

void PrideLayer::onEnter(){
    Layer::onEnter();
}

void PrideLayer::onExit(){
    Layer::onExit();
}

void PrideLayer::drawLayerUi(){
    
    for (int i=0; i<4; i++) {
        ExchangePropCell* cell = ExchangePropCell::create(1, 1, "");
        cell->setPosition(310+220*i,370);
        addChild(cell);
    }
    
}