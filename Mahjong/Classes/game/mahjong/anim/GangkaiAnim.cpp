//
//  GangkaiAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/22.
//
//

#include "game/mahjong/anim/GangkaiAnim.hpp"
#include "game/mahjong/jong/Jong.h"
#include "game/utils/SeatIdUtil.h"
#include "game/mahjong/core/MahjongView.h"



GangkaiAnim* GangkaiAnim::create(int seatId,bool qiang){
    GangkaiAnim* gangkai = new GangkaiAnim();
    if(gangkai&&gangkai->init(seatId,qiang)){
        gangkai->autorelease();
        return gangkai;
    }
    CC_SAFE_DELETE(gangkai);
    return NULL;

}

bool GangkaiAnim::init(int seatId,bool qiang){
    if(!Layer::init()){
    
        return false;
    }
    showCircle(seatId,qiang);
    return true;

}


void GangkaiAnim::showCircle(int seatId,bool qiang){
    auto cirlce1 = Sprite::create("gameview/circle_light.png");
    cirlce1->setPosition(getPosbySeat(seatId));
    cirlce1->setScale(0.3f);
    cirlce1->setOpacity(77);
    addChild(cirlce1);
    cirlce1->runAction(Sequence::create(Spawn::create(FadeTo::create(4.0f/24,180),ScaleTo::create(4.0/24, 2.0f), NULL), Spawn::create(FadeTo::create(2.0f/24,255),ScaleTo::create(2.0/24, 1.0f), NULL),NULL));
    
    auto circle2 = Sprite::create("gameview/circle_2.png");
    circle2->setPosition(getPosbySeat(seatId));
    addChild(circle2);
    circle2->setOpacity(77);
    circle2->setScale(0.2f);
    circle2->runAction(Sequence::create(DelayTime::create(4.0f/24),Spawn::create(FadeTo::create(3.0f/24,180),ScaleTo::create(3.0/24, 1.5f), NULL),Spawn::create(FadeTo::create(2.0f/24,255),ScaleTo::create(2.0/24, 1.0f),NULL), NULL));
    
    auto circle3= Sprite::create("gameview/circle_3.png");
    circle3->setPosition(getPosbySeat(seatId));
    circle3->setOpacity(77);
    addChild(circle3);
    circle3->setScale(0.5f);
    circle3->runAction(Sequence::create(DelayTime::create(4.0f/24),Spawn::create(FadeTo::create(3.0f/24,180),ScaleTo::create(3.0/24, 1.5f), NULL),Spawn::create(FadeTo::create(2.0f/24,255),ScaleTo::create(2.0/24, 1.0f),NULL),RotateTo::create(3, -173),   CallFunc::create([=](){
        showPokersLight(seatId);
        ((MahjongView*)getParent())->showHandPokerOver(seatId);
    }), NULL));
    
    auto flower = Sprite::create();
    flower->setPosition(getPosbySeat(seatId));
    flower->setVisible(false);
    addChild(flower);
    flower->runAction(Sequence::create(DelayTime::create(8.0f/24),CallFunc::create([=](){
        flower->setVisible(true);
        showFlower(flower);
    }), NULL));
    
    auto light = Sprite::create();
    light->setPosition(getPosbySeat(seatId));
    addChild(light);
    light->runAction(Sequence::create(DelayTime::create(17.0/24),CallFunc::create([=](){
        light->runAction(Repeat::create(Sequence::create(CallFunc::create([=](){
            showLight(light);
        }),DelayTime::create(6.0/24), NULL),10));
        
    }), NULL));
    
    auto bg = Sprite::create("gameview/shadow.png");
    bg->setPosition(getPosbySeat(seatId));
    addChild(bg,-1);
    bg->setOpacity(77);
    bg->setVisible(false);
    bg->runAction(Sequence::create(DelayTime::create(14.0f/24),CallFunc::create([=](){
    bg->setVisible(true);
    }), FadeTo::create(4.0/24,255), NULL));
    
    auto gang = Sprite::create("gameview/gang_kai.png");
    if(qiang){
        gang->setTexture("gameview/qg_font_qiang.png");
    }
    gang->setPosition(getPosbySeat(seatId));
    addChild(gang);
    gang->setVisible(false);
    gang->runAction(Sequence::create(DelayTime::create(13.0/24),CallFunc::create([=](){
        gang->setVisible(true);
        gang->setOpacity(77);
        gang->setScale(2.0f);
    }), Spawn::create(ScaleTo::create(3.0/24, 0.9f),FadeTo::create(3.0/24, 255), NULL),ScaleTo::create(3.0/24, 1.0f),NULL));
    
    auto kai = Sprite::create("gameview/gang_kai2.png");
    if(qiang){
        kai->setTexture("gameview/qg_font_gang.png");
    }
    kai->setPosition(getPosbySeat(seatId));
    addChild(kai);
    kai->setVisible(false);
    kai->runAction(Sequence::create(DelayTime::create(16.0/24),CallFunc::create([=](){
        kai->setVisible(true);
        kai->setOpacity(77);
        kai->setScale(2.0f);
    }), Spawn::create(ScaleTo::create(3.0/24, 0.9f),FadeTo::create(3.0/24, 255), NULL),ScaleTo::create(3.0/24, 1.0f),NULL));
    
    //自摸动画转向
    if(seatId == ClientSeatId::left){
        cirlce1->setRotation(90);
        circle2->setRotation(90);
        circle3->setRotation(90);
        light->setRotation(90);
        flower->setRotation(90);
        bg->setRotation(90);
        gang->setRotation(90);
        kai->setRotation(90);
    }else if(seatId == ClientSeatId::opposite){
        cirlce1->setRotation(180);
        circle2->setRotation(180);
        circle3->setRotation(180);
        light->setRotation(180);
        flower->setRotation(180);
        bg->setRotation(180);
        gang->setRotation(180);
        kai->setRotation(180);
    }else if(seatId == ClientSeatId::right){
        cirlce1->setRotation(270);
        circle2->setRotation(270);
        circle3->setRotation(270);
        light->setRotation(270);
        bg->setRotation(270);
        flower->setRotation(270);
        gang->setRotation(270);
        kai->setRotation(270);
    }

}

void GangkaiAnim::showPokersLight(int seatId){
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

void GangkaiAnim::showFlower(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<13;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/flower_light_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));
}

void GangkaiAnim::showLight(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<6;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/flower_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));
}

Point GangkaiAnim :: getPosbySeat(int seatId){
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


