//
//  PlayerCpgAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/22.
//
//

#include "mahjong/anim/PlayerCpgAnim.hpp"
#include "mahjong/utils/SeatIdUtil.h"

PlayerCpgAnim* PlayerCpgAnim::create(CpgType type,int seatId){
    PlayerCpgAnim* anim = new PlayerCpgAnim();
    if(anim && anim->init(type, seatId)){
        anim->autorelease();
        return anim;
    }
    CC_SAFE_DELETE(anim);
    return anim;
}

bool PlayerCpgAnim::init(CpgType type,int seatId){
    if(!Layer::init()){
    
        return false;
    }
    showCpgAnim(type,seatId);
    return true;
}


void PlayerCpgAnim::showCpgAnim(CpgType type,int seatId){
    Sprite* infi = Sprite::create();
    infi->setPosition(getPosBySeatId(seatId));
    addChild(infi);
    infi->runAction(Sequence::create(CallFunc::create([=](){
        showLight(infi);
    }),DelayTime::create(3.0/24),CallFunc::create([=](){
        auto box = Sprite::create("gameview/cpg_bg.png");
        box->setPosition(getPosBySeatId(seatId));
        addChild(box);
        box->runAction(Sequence::create(DelayTime::create(2.0f/24),ScaleTo::create(1.0f/24,1.2f),ScaleTo::create(1.0f/24,1.0),ScaleTo::create(1.0f/24, 0.8f),ScaleTo::create(1.0f/24, 1.0f), NULL));
    }), DelayTime::create(2.0/24),CallFunc::create([=](){
        auto text = Sprite::create(getImageNameByType(type));
        text->setPosition(getPosBySeatId(seatId));
        addChild(text);
        text->setScale(2.0f);
        text->setOpacity(100);
        text->runAction(Sequence::create(Spawn::create(FadeTo::create(4.0/24,255),
                                                       ScaleTo::create(4.0/24, 0.8f),
                                                       NULL), ScaleTo::create(2.0/24, 1.0f),DelayTime::create(12.0/24), CallFunc::create([=](){
            this->removeFromParent();
        }), NULL));
    }),NULL));
}

void PlayerCpgAnim::showLight(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<7;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/cpg_light_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));
}

Point PlayerCpgAnim::getPosBySeatId(int seatId){
    if(seatId==ClientSeatId::hero){
         return Point(640,280);
    
    }else if(seatId== ClientSeatId::left){
        return Point(270,415);
    
    }else if(seatId== ClientSeatId::right){
        return Point(1010,415);

    
    }else if(seatId == ClientSeatId::opposite){
    
        return Point(640,590);
    }
}

std::string PlayerCpgAnim::getImageNameByType(CpgType type){
    std::string imageName = "";
    if(type == CpgType::chi){
        imageName= "gameview/chi.png";
    }else if(type==CpgType::peng){
    imageName= "gameview/peng.png";
    }else if(type==CpgType::gang||type==CpgType::angang||type==CpgType::penggang){
    imageName= "gameview/gang.png";
    
    }else if(type ==CpgType::ting){
    imageName= "gameview/mj_ting.png";
    }
    return imageName;
}






