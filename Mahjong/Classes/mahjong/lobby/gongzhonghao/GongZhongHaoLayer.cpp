//
//  GameGongGao.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/6.
//
//

#include "mahjong/lobby/gongzhonghao/GongZhongHaoLayer.hpp"
#include "http/image/UrlImageMannger.h"
#include "mahjong/GameConfig.h"
#include "userdata/UserData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

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
    
    haoma = Label::createWithSystemFont(UserData::getInstance()->getGongZhongHao(), "arial", 32);
    haoma->setColor(Color3B(153,39,0));
    haoma->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    haoma->setPosition(685,545);
    addChild(haoma);
    
//    auto copyWxImg  = MenuItemImage::create("gongzhonghao/copy_1.png", "gongzhonghao/copy_2.png", CC_CALLBACK_0(GongZhongHaoLayer::copyText,this));
//    auto copyMenu = Menu::create(copyWxImg,NULL);
//    copyMenu->setPosition(945,550);
//    addChild(copyMenu);
    
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

void GongZhongHaoLayer::copyText(){
    std::string content = haoma->getString();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->copyToPasteboard(content);
#endif
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->copyToPasteboard(content);
#endif
    toast();
}

void GongZhongHaoLayer::toast(){
    auto bg = Sprite::create("common/toast_bg.png");
    bg->setAnchorPoint(Point::ANCHOR_MIDDLE);
    bg->setPosition(650,300);
    bg->setScaleX(0.2);
    addChild(bg);
    auto shui = Label::createWithSystemFont("复制成功","arial",26);
    shui->setColor(Color3B(255,183,64));
    shui->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    shui->setPosition(600,300);
    addChild(shui);
    
    bg->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        bg->setVisible(false);
    }), NULL));
    shui->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        shui->setVisible(false);
    }), NULL));
}
