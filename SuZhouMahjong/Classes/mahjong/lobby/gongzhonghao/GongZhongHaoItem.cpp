//
//  GongGaoItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#include "mahjong/lobby/gongzhonghao/GongZhongHaoItem.hpp"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"


GongZhongHaoItem* GongZhongHaoItem::create(int index){
    auto gongGao = new GongZhongHaoItem();
    if(nullptr != gongGao && gongGao->init(index)){
        gongGao->autorelease();
        return gongGao;
    }else{
        CC_SAFE_DELETE(gongGao);
        return nullptr;
    }
}


bool GongZhongHaoItem::init(int index){
    if(!Layer::init()){
        return false;
    }
    auto content = Sprite::create();
    content->setTexture(getImageByIndex(index));
    content->setPosition(780,320);
    addChild(content);
    return true;
}


std::string GongZhongHaoItem::getImageByIndex(int index){
    if(index == 0){
        return "gongzhonghao/tu1.png";
    }else if(index == 1){
        return "gongzhonghao/tu2.png";
    }else if(index == 2){
        return "gongzhonghao/tu3.png";
    }else if(index == 3){
        return "gongzhonghao/tu4.png";
    }else{
        return "";
    }
}

