//
//  RankLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#include "game/mahjong/activities/RankLayer.hpp"
bool RankLayer::init(){
    if(!Layer::init()){
        return false;
    }
    drawLayerUi();
    return true;
}

void RankLayer::onEnter(){
    Layer::onEnter();
}

void RankLayer::onExit(){
    Layer::onExit();
}

void RankLayer::drawLayerUi(){
    
    auto content_2 = Sprite::create("activities/act_conten_2.jpg");
    content_2->setPosition(640,290);
    addChild(content_2);
    
    auto weekName = Label::createWithSystemFont("hello", "arial", 24);
    weekName->setColor(Color3B::BLACK);
    weekName->setPosition(600,450);
    addChild(weekName);
    
    auto weekLequan = Label::createWithSystemFont("10000", "arial", 24);
    weekLequan->setColor(Color3B::BLACK);
    weekLequan->setPosition(950,450);
    addChild(weekLequan);
    
    
}