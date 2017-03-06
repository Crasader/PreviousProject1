//
//  GameGongGao.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#include "mahjong/gonggao/GameGongGaoLayer.hpp"
#include "mahjong/utils/GameConfig.h"
#include "http/image/UrlImageMannger.h"

GameGongGaoLayer* GameGongGaoLayer::create(GameGongGao gonggaoData){
    auto gongGao = new GameGongGaoLayer();
    if(nullptr != gongGao && gongGao->init(gonggaoData)){
        gongGao->autorelease();
        return gongGao;
    }else{
        CC_SAFE_DELETE(gongGao);
        return nullptr;
    }
}

bool GameGongGaoLayer::init(GameGongGao gonggaoData){
    if(!Layer::init()){
        return false;
    }
    myGongGao = gonggaoData;
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    

    auto day_bg = Sprite::create("daily/daily_bg.png");
    day_bg->setPosition(640, 360);
    addChild(day_bg);
    
    auto title = Sprite::create("mjlobby/gong_gao_title.png");
    title->setPosition(640,640);
    addChild(title);

    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(GameGongGaoLayer::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1050,610);
    addChild(menu,3);
    
    showIndex =0;
    for(int i=0;i<gonggaoData.gongGaoData.size();i++){
        GongGaoItem* gonggao = GongGaoItem::create(gonggaoData.gongGaoData.at(i));
        gonggao->setTag(i);
        addChild(gonggao);
        if(i==0){
            gonggao->setVisible(true);
        }else{
            gonggao->setVisible(false);
        }
        contents.push_back(gonggao);
        
        auto bulbble = Sprite::create();
        bulbble->setPosition(getBubblePos(gonggaoData.gongGaoData.size(),i));
        addChild(bulbble,2);
        bubbles.push_back(bulbble);
        if(i==0){
            bubbles.at(i)->setTexture("mjlobby/bubble_2.png");
        }else{
            bubbles.at(i)->setTexture("mjlobby/bubble_1.png");
        }

    }
    schedule(schedule_selector(GameGongGaoLayer::updateGongGao), atoi(gonggaoData.gongGaoData.at(0).showTime.c_str()), CC_REPEAT_FOREVER, 0);
    return true;
}

void GameGongGaoLayer::closeView(){
    removeFromParent();
}

Point GameGongGaoLayer::getBubblePos(int size,int index){
    return Point(int(1064-32*(size-index)),140);
}

void GameGongGaoLayer::updateGongGao(float dt){
    showIndex =  (showIndex+1)%myGongGao.gongGaoData.size();
    for(auto var : contents){
        if(showIndex == var->getTag()){
            var->setVisible(true);
        }else{
            var->setVisible(false);
        }
    }
    for (int i=0 ;i<bubbles.size();i++) {
        if(i==showIndex){
            bubbles.at(i)->setTexture("mjlobby/bubble_2.png");
        }else{
            bubbles.at(i)->setTexture("mjlobby/bubble_1.png");
        }
    }
}
