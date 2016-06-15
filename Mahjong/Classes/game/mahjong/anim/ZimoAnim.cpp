//
//  ZimoAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/25.
//
//

#include "game/mahjong/anim/ZimoAnim.hpp"
#include "game/utils/SeatIdUtil.h"
#include "game/mahjong/core/MahjongView.h"

ZimoAnim* ZimoAnim::create(int seatId){
    ZimoAnim* anim = new ZimoAnim();
    if(anim&& anim->init(seatId)){
        anim->autorelease();
        return anim;
    }
    CC_SAFE_DELETE(anim);
    return NULL;

}

bool ZimoAnim::init(int seatId){
    if(!Layer::init()){
        return false;
    
    }
    showZimoAnim(seatId);
    return true;
}


void ZimoAnim:: showZimoAnim(int seatId){
    
    auto shadow = Sprite::create("gameview/zimo_shadow.png");
    shadow->setPosition(getPosbySeat(seatId));
    shadow->setVisible(false);
    addChild(shadow);
    shadow->setOpacity(80);
    shadow->runAction(Sequence::create(DelayTime::create(11.0/24),CallFunc::create([=](){
        shadow->setVisible(true);
    }),FadeTo::create(5.0f/24,255) ,NULL));
    
    auto color = Sprite::create();
    color->setPosition(getPosbySeat(seatId));
    color->setVisible(false);
    addChild(color);
    Sprite* nimo = Sprite::create();
    nimo->setPosition(getPosbySeat(seatId));
    addChild(nimo);
    color->runAction(Sequence::create(DelayTime::create(9.0/24),CallFunc::create([=](){
        color->setVisible(true);
    }),CallFunc::create([=](){
        showColorAnim(color);
    }),DelayTime::create(6.0f/24),Repeat::create(Sequence::create(CallFunc::create([=](){
        showColorLightAnim(nimo);
    }),DelayTime::create(7.0/24), NULL), 20), NULL));
    
    auto redStar = Sprite::create("gameview/wuxin_samll_left_1.png");
    redStar->setPosition(getPosbySeat(seatId));
    redStar->setVisible(false);
    redStar->setScale(0.5f);
    addChild(redStar);
    redStar->runAction(Sequence::create(DelayTime::create(2.0/24),CallFunc::create([=](){
        redStar->setVisible(true);
    }),ScaleTo::create(3.0f/24,1.2f), ScaleTo::create(2.0f/24,1.0f),Repeat::create(Sequence::create(CallFunc::create([=](){
        if(getRedLight()){
            redStar->setTexture("gameview/wuxin_samll_left_1.png");
        }else{
            redStar->setTexture("gameview/wuxin_samll_left_2.png");
        }
        setRedLight(!getRedLight());
    }),DelayTime::create(3.0/24), NULL), 50), NULL));
    
    auto greenStar = Sprite::create("gameview/wuxin_samll_right_1.png");
    greenStar->setPosition(getPosbySeat(seatId));
    greenStar->setVisible(false);
    greenStar->setScale(0.5f);
    addChild(greenStar);
    greenStar->runAction(Sequence::create(DelayTime::create(5.0/24),CallFunc::create([=](){
        greenStar->setVisible(true);
    }),ScaleTo::create(3.0f/24,1.2f), ScaleTo::create(2.0f/24,1.0f),Repeat::create(Sequence::create(CallFunc::create([=](){
        if(getRedLight()){
            greenStar->setTexture("gameview/wuxin_samll_right_1.png");
        }else{
            greenStar->setTexture("gameview/wuxin_samll_right_2.png");
        }
       setGreenLight(!getGreenLight());
    }),DelayTime::create(3.0/24), NULL), 50), NULL));
    
    
    auto fontZi = Sprite::create("gameview/font_zi.png");
    fontZi->setPosition(getPosbySeat(seatId));
    fontZi->setVisible(false);
    fontZi->setScale(1.6f);
    fontZi->setOpacity(80);
    addChild(fontZi,1);
    fontZi->runAction(Sequence::create(DelayTime::create(2.0/24),CallFunc::create([=](){
        fontZi->setVisible(true);
    }),Spawn::create(ScaleTo::create(3.0f/24,0.6f),FadeTo::create(3.0f/24,255),NULL), ScaleTo::create(2.0f/24,1.0f), NULL));
    
    auto fontMo = Sprite::create("gameview/fon_mo.png");
    fontMo->setPosition(getPosbySeat(seatId));
    fontMo->setVisible(false);
    fontMo->setScale(1.6f);
    fontMo->setOpacity(80);
    addChild(fontMo,1);
    fontMo->runAction(Sequence::create(DelayTime::create(9.0/24),CallFunc::create([=](){
        fontMo->setVisible(true);
        showPokersLight(seatId);
        ((MahjongView*)getParent())->showHandPokerOver(seatId);
    }),Spawn::create(ScaleTo::create(3.0f/24,0.6f),FadeTo::create(3.0f/24,255),NULL), ScaleTo::create(2.0f/24,1.0f), NULL));
    
  
    
    auto start5 = Sprite::create();
    start5->setPosition(getPosbySeat(seatId));
    addChild(start5);
    auto  purple = Sprite::create("gameview/wuxin_big_1.png");
    //    purple->setPosition(getPosbySeat(seatId));
    start5->addChild(purple);
    auto purpleBig = Sprite::create("gameview/wuxin_big_2.png");
    //    purpleBig->setPosition(getPosbySeat(seatId));
    start5->addChild(purpleBig);
    auto lightBig = Sprite::create("gameview/wuxin_big_light.png");
    start5->addChild(lightBig);
    
    Sprite* demo = Sprite::create();
    demo->setPosition(getPosbySeat(seatId));
    addChild(demo);
    
    start5->runAction(Sequence::create(ScaleTo::create(3.0f/24, 1.5f),ScaleTo::create(2.0f/24, 0.8f), ScaleTo::create(2.0f/24, 1.0f),Repeat::create(Sequence::create(CallFunc::create([=](){
        showStarligth(demo);
    }),DelayTime::create(8.0/24), NULL), 100),NULL));
    
    
    //自摸动画转向
//    if(seatId == ClientSeatId::left){
//        shadow->setRotation(90);
//        color->setRotation(90);
//        nimo->setRotation(90);
//        redStar->setRotation(90);
//        greenStar->setRotation(90);
//        fontZi->setRotation(90);
//        fontMo->setRotation(90);
//        start5->setRotation(90);
//        demo->setRotation(90);
//    }else if(seatId == ClientSeatId::opposite){
//        shadow->setRotation(180);
//        color->setRotation(180);
//        redStar->setRotation(180);
//        nimo->setRotation(180);
//        greenStar->setRotation(180);
//        fontZi->setRotation(180);
//        fontMo->setRotation(180);
//        start5->setRotation(180);
//        demo->setRotation(180);
//    }else if(seatId == ClientSeatId::right){
//        shadow->setRotation(270);
//        color->setRotation(270);
//        redStar->setRotation(270);
//        greenStar->setRotation(270);
//        nimo->setRotation(270);
//        fontZi->setRotation(270);
//        fontMo->setRotation(270);
//        start5->setRotation(270);
//        demo->setRotation(270);
//    }
}



void ZimoAnim::showPokersLight(int seatId){
    //胡牌玩家亮牌前,光效动画
    Point pos1;
    Point pos2;
    
    Sprite* guangXiao1 = Sprite::create("result/hupai_light.png");
    guangXiao1->setPosition(pos1);
    guangXiao1->setOpacity(77);
    addChild(guangXiao1);
    
    Sprite* guangXiao2 = Sprite::create("result/hupai_light.png");
    addChild(guangXiao2);
    guangXiao2->setOpacity(77);
    guangXiao2->setPosition(pos2);
    
    float scaleX;
    
    if(seatId == ClientSeatId::opposite){
        pos1 = Point(300,600);
        pos2 = Point(900,600);
        scaleX = 3.0;
    }else if(seatId == ClientSeatId::left){
        pos1 = Point(200,600);
        pos2 = Point(200,200);
        guangXiao1->setRotation(90);
        guangXiao2->setRotation(90);
        scaleX = 2.0;
    }else if(seatId == ClientSeatId::right){
        pos1 = Point(1100,600);
        pos2 = Point(1100,200);
        guangXiao1->setRotation(90);
        guangXiao2->setRotation(90);
        scaleX = 2.0;
    }else{
        pos1 = Point(200,100);
        pos2 = Point(1000,100);
        scaleX = 3.0;
    }
    
    guangXiao1->runAction(Sequence::create(Spawn::create(ScaleTo::create(5.0/24, scaleX,1.2f),MoveTo::create(5.0/24, pos2),
                                                         FadeTo::create(5.0/24, 200),NULL),
                                           Spawn::create(ScaleTo::create(5.0/24, 1.0f,1.0f),MoveTo::create(5.0/24, pos2), FadeTo::create(5.0/24, 0), NULL),
                                           NULL));
    
    
    guangXiao2->runAction(Sequence::create(Spawn::create(ScaleTo::create(5.0/24,scaleX,1.2f),MoveTo::create(5.0/24, pos1), FadeTo::create(5.0/24, 200),NULL),
                                           Spawn::create(ScaleTo::create(5.0/24, 1.0f,1.0f),MoveTo::create(5.0/24, pos2), FadeTo::create(5.0/24, 0),NULL),NULL));
}

Point ZimoAnim :: getPosbySeat(int seatId){
    if(seatId == ClientSeatId::left){
        return Point(280,360);
    }else if(seatId == ClientSeatId::right){
        return Point(930,360);
    }else if(seatId == ClientSeatId::opposite){
        return Point(640,550);
    }else {
        
        return Point(640,220);
    }
}

void ZimoAnim::showStarligth(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<4;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/star_5_light_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(2.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));

}

void ZimoAnim::showColorAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<4;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/color_light_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(2.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(action);

}

void ZimoAnim::showColorLightAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<8;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/color_bg_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(action);
}

