//
//  CompeititionPlate.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/20.
//
//

#include "mahjong/lobby/competition/CompeititionPlate.hpp"

bool CompeititionPlate::init(){
    if(!Layer::init()){
        return false;
    }
    auto comebg = Sprite::create("competition/lobby_com_bg.png");
    comebg->setPosition(640,360);
    addChild(comebg);
    
    auto title = Sprite::create("competition/com_title.png");
    title->setPosition(640,645);
    addChild(title);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(CompeititionPlate::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1090,635);
    addChild(menu,3);
    
    return true;
}

void CompeititionPlate::closeView(){
    removeFromParent();
}
