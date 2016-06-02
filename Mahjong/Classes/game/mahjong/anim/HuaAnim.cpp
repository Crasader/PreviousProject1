//
//  HuaAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/9.
//
//

#include "game/mahjong/anim/HuaAnim.hpp"
#include "game/utils/SeatIdUtil.h"

HuaAnim* HuaAnim::create(std::vector<Jong*> jongs,int seatId,CallFunc* func){
    HuaAnim* anim = new HuaAnim();
    if(anim && anim->init(jongs, seatId,func)){
        anim->autorelease();
        return anim;
    }
    
    CC_SAFE_DELETE(anim);
    return NULL;
}


bool HuaAnim::init(std::vector<Jong*> jongs,int seatId,CallFunc* func){
    for(int i=0;i<jongs.size();i++){
        Jong* jong = Jong::create();
        jong->setPosition(getPosBySeatId(seatId).x-30*jongs.size()+63*i,getPosBySeatId(seatId).y);
        jong->showJong(herohand,jongs.at(i)->getJongType());
        addChild(jong);
        jong->setScale(0.2f);
        jong->setOpacity(77);
        jong->runAction(Sequence::create(Spawn::create(ScaleTo::create(4.0f/24, 1.5f),FadeTo::create(4.0f/24, 180.0f), NULL), CallFunc::create([=](){
            Sprite* bot = Sprite::create();
            bot->setPosition(getPosBySeatId(seatId).x-10-30*jongs.size()+63*i,getPosBySeatId(seatId).y);
            addChild(bot);
            showHuaAnim(bot);
        }),Spawn::create(ScaleTo::create(3.0f/24, 0.8f),FadeTo::create(3.0f/24, 255.0f), NULL),DelayTime::create(16.0f/24),Spawn::create(MoveTo::create(3.0f/24, getHuaPosBySeatId(seatId)),ScaleTo::create(3.0f/24, 0.2f),NULL),func, CallFunc::create([=](){
                this->removeFromParent();
        }), NULL));
    
    }
       return true;
}



void HuaAnim::showHuaAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<8;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/flower_anim_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action,CallFunc::create([=](){
        sprite->setVisible(false);
    }), NULL));
    
}


Point HuaAnim::getPosBySeatId(int seatId){
    if(seatId == ClientSeatId::left){
        return Point(300,400);
    }else if(seatId == ClientSeatId::opposite){
        return Point(640,550);
    }else if(seatId == ClientSeatId::right){
     return Point(980,400);
    }else {
        return Point(640,200);
    }
}

Point HuaAnim::getHuaPosBySeatId(int seatId){
    if(seatId == ClientSeatId::left){
        return Point(45,545);
    }else if(seatId == ClientSeatId::opposite){
        return Point(820,615);
    }else if(seatId == ClientSeatId::right){
        return Point(1230,545);
    }else {
        return Point(300,170);
    }
}