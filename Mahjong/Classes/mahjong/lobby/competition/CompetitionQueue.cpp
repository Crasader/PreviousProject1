//
//  CompetitionQueue.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/17.
//
//

#include "mahjong/lobby/competition/CompetitionQueue.hpp"


//competition_queue_bg.png

bool CompetitionQueue::init(){
    if(!Layer::init()){
        return false;
    }
    auto queueBg = Sprite::create("competition/competition_queue_bg.png");
    queueBg->setPosition(640,360);
    addChild(queueBg);
    
    return true;
}
