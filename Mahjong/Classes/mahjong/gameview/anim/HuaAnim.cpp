//
//  HuaAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/9.
//
//

#include "mahjong/gameview/anim/HuaAnim.hpp"
#include "mahjong/state/GameData.h"
#include "mahjong/utils/SeatIdUtil.h"

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
        jong->runAction(Sequence::create(Spawn::create(ScaleTo::create(3.0f/24, 1.5f),FadeTo::create(3.0f/24, 180.0f), NULL), CallFunc::create([=](){
            Sprite* bot = Sprite::create();
            bot->setPosition(getPosBySeatId(seatId).x-10-30*jongs.size()+63*i,getPosBySeatId(seatId).y);
            addChild(bot);
            showHuaAnim(bot);
        }),Spawn::create(ScaleTo::create(2.0f/24, 0.8f),FadeTo::create(2.0f/24, 255.0f), NULL),DelayTime::create(10.0f/24),Spawn::create(MoveTo::create(2.0f/24, getHuaPosBySeatId(seatId)),ScaleTo::create(2.0f/24, 0.2f),NULL),func, CallFunc::create([=](){
                removeFromParent();
        }), NULL));
    
    }
       return true;
}



void HuaAnim::showHuaAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<8;i++)
    {
        std::string imageName = StringUtils::format ("gameview/flower_anim_%d.png",i);
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
    int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId);
    if(clientSeatId == ClientSeatId::left){
        return Point(300,400);
    }else if(clientSeatId == ClientSeatId::opposite){
        return Point(640,550);
    }else if(clientSeatId == ClientSeatId::right){
     return Point(980,400);
    }else {
        return Point(640,200);
    }
}

Point HuaAnim::getHuaPosBySeatId(int seatId){
    int clientSeatId = SeatIdUtil::getClientSeatId(GAMEDATA::getInstance()->getHeroSeatId(), seatId);
    if(clientSeatId == ClientSeatId::left){
        return Point(45,545);
    }else if(clientSeatId == ClientSeatId::opposite){
        return Point(820,615);
    }else if(clientSeatId == ClientSeatId::right){
        return Point(1230,545);
    }else {
        return Point(300,170);
    }
}
