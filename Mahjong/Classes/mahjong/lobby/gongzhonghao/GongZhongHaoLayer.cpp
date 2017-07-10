//
//  GameGongGao.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#include "mahjong/lobby/gongzhonghao/GongZhongHaoLayer.hpp"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"

GongZhongHaoLayer* GongZhongHaoLayer::create(){
    auto gongGao = new GongZhongHaoLayer();
    if(nullptr != gongGao && gongGao->init()){
        gongGao->autorelease();
        return gongGao;
    }else{
        CC_SAFE_DELETE(gongGao);
        return nullptr;
    }
    
}

bool GongZhongHaoLayer::init(){
    if(!Layer::init()){
        return false;
    }

    
    auto day_bg = Sprite::create("shop/shop_bg.png");
    day_bg->setTag(1024);
    day_bg->setPosition(640, 360);
    addChild(day_bg);
    
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(GongZhongHaoLayer::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1070,630);
    addChild(menu,3);
    
    auto title = Sprite::create("gongzhonghao/gzh_title.png");
    title->setPosition(640,610);
    addChild(title);
    
    
    auto girl = Sprite::create("gongzhonghao/ren.png");
    girl->setPosition(300,350);
    addChild(girl);
    
    auto weixin = Sprite::create("gongzhonghao/zi_wx_gzh.png");
    weixin->setPosition(600,545);
    addChild(weixin);
    
    showIndex =0;
    for(int i=0;i<totalPage;i++){
        GongZhongHaoItem* gonggao = GongZhongHaoItem::create(i);
        gonggao->setTag(i);
        addChild(gonggao);
        if(i==0){
            gonggao->setVisible(true);
        }else{
            gonggao->setVisible(false);
        }
        contents.push_back(gonggao);
        
        auto bulbble = Sprite::create();
        bulbble->setPosition(getBubblePos(4,i));
        addChild(bulbble,2);
        bubbles.push_back(bulbble);
        if(i==0){
            bubbles.at(i)->setTexture("gongzhonghao/bubble_2.png");
        }else{
            bubbles.at(i)->setTexture("gongzhonghao/bubble_1.png");
        }
        
    }

    schedule(schedule_selector(GongZhongHaoLayer::updateGongGao),6, CC_REPEAT_FOREVER, 0);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GongZhongHaoLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GongZhongHaoLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GongZhongHaoLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
    return true;
}

void GongZhongHaoLayer::closeView(){
    removeFromParent();
}

Point GongZhongHaoLayer::getBubblePos(int size,int index){
    return Point(int(820-32*(size-index)),110);
}

void GongZhongHaoLayer::updateGongGao(float dt){
    showIndex =  (showIndex+1)%totalPage;
    for(auto var : contents){
        if(showIndex == var->getTag()){
            var->setVisible(true);
        }else{
            var->setVisible(false);
        }
    }
    for (int i=0 ;i<bubbles.size();i++) {
        if(i==showIndex){
            bubbles.at(i)->setTexture("gongzhonghao/bubble_2.png");
        }else{
            bubbles.at(i)->setTexture("gongzhonghao/bubble_1.png");
        }
    }
}


bool GongZhongHaoLayer::onTouchBegan(Touch *touch, Event  *event){
    if(((Sprite*)getChildByTag(1024))->getBoundingBox().containsPoint(touch->getLocation())){
        lastPos = touch->getLocation();
        return true;
    }
    return false;
}


void GongZhongHaoLayer::onTouchMoved(Touch *touch, Event  *event){
    
    }


void GongZhongHaoLayer::onTouchEnded(Touch *touch, Event  *event){
    Point currentPos = touch->getLocation();
    float dis = getDistance(lastPos,currentPos);
    if(dis>50){
        if(currentPos.x>lastPos.x){
            showIndex =  (showIndex+1)%totalPage;
        }else{
            int temp = showIndex-1;
            if(temp<0){
                temp = (int)contents.size()-1;
            }
            showIndex =  temp%totalPage;
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
                bubbles.at(i)->setTexture("gongzhonghao/bubble_2.png");
            }else{
                bubbles.at(i)->setTexture("gongzhonghao/bubble_1.png");
            }
        }

    }
}

float GongZhongHaoLayer::getDistance(Point s, Point e){
    return sqrt(pow(e.x-s.x, 2)+pow(e.y-s.y, 2));

}
