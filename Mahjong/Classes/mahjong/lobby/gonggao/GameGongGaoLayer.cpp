//
//  GameGongGao.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#include "mahjong/lobby/gonggao/GameGongGaoLayer.hpp"
#include "mahjong/GameConfig.h"
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
    auto day_bg = Sprite::create("shop/shop_bg.png");
    day_bg->setTag(1024);
    day_bg->setPosition(640, 360);
    addChild(day_bg);
    
    auto title = Sprite::create("gonggao/gonggao_title.png");
    title->setPosition(640,620);
    addChild(title);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(GameGongGaoLayer::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1070,630);
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
        bulbble->setPosition(getBubblePos((int)gonggaoData.gongGaoData.size(),i));
        addChild(bulbble,2);
        bubbles.push_back(bulbble);
        if(i==0){
            bubbles.at(i)->setTexture("gonggao/bubble_2.png");
        }else{
            bubbles.at(i)->setTexture("gonggao/bubble_1.png");
        }
        
    }
    schedule(schedule_selector(GameGongGaoLayer::updateGongGao), atoi(gonggaoData.gongGaoData.at(0).showTime.c_str()), CC_REPEAT_FOREVER, 0);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameGongGaoLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameGongGaoLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameGongGaoLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
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
            bubbles.at(i)->setTexture("gonggao/bubble_2.png");
        }else{
            bubbles.at(i)->setTexture("gonggao/bubble_1.png");
        }
    }
}


bool GameGongGaoLayer::onTouchBegan(Touch *touch, Event  *event){
    if(((Sprite*)getChildByTag(1024))->getBoundingBox().containsPoint(touch->getLocation())){
        lastPos = touch->getLocation();
        return true;
    }
    return false;
}


void GameGongGaoLayer::onTouchMoved(Touch *touch, Event  *event){
    
    }


void GameGongGaoLayer::onTouchEnded(Touch *touch, Event  *event){
    Point currentPos = touch->getLocation();
    float dis = getDistance(lastPos,currentPos);
    if(dis>50){
        if(currentPos.x>lastPos.x){
            showIndex =  (showIndex+1)%myGongGao.gongGaoData.size();
        }else{
            int temp = showIndex-1;
            if(temp<0){
                temp = (int)contents.size()-1;
            }
            showIndex =  temp%myGongGao.gongGaoData.size();
        }
        
        for(auto var : contents){
            if(showIndex == var->getTag()){
                var->setVisible(true);
            }else{
                var->setVisible(false);
            }
        }
        for (int i=0 ;i<bubbles.size();i++) {
            if(i==showIndex){
                bubbles.at(i)->setTexture("gonggao/bubble_2.png");
            }else{
                bubbles.at(i)->setTexture("gonggao/bubble_1.png");
            }
        }

    }
}

float GameGongGaoLayer::getDistance(Point s, Point e){
    return sqrt(pow(e.x-s.x, 2)+pow(e.y-s.y, 2));

}
