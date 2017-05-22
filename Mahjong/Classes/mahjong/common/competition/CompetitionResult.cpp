//
//  CompetitionResult.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/22.
//
//

#include "mahjong/common/competition/CompetitionResult.hpp"

bool CompetitionResult::init(){
    if(!Layer::init()){
        return false;
    }
    auto reslut_bg = Sprite::create("result/result_bg.jpg");
    reslut_bg->setPosition(640, 360);
    addChild(reslut_bg,-1);
    return true;
}

void CompetitionResult::showCompetiotionResult(std::string type,std::string rank,std::string pride,std::string score){
    
}
