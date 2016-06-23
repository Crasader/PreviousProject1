//
//  OutFogAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/1.
//
//

#include "OutFogAnim.hpp"


OutFogAnim* OutFogAnim::create(Point pos){
    OutFogAnim* ret = new OutFogAnim();
    if(ret && ret->init(pos)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool OutFogAnim::init(Point pos){
    auto spr = Sprite::create();
    spr->setPosition(pos);
    addChild(spr);
    spr->runAction(Sequence::create(CallFunc::create([=](){
        showFogAnim(spr);
    }),DelayTime::create(6.0f/24),CallFunc::create([=](){
        removeFromParent();
    }), NULL));
    return true;
}

void OutFogAnim::showFogAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<6;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/player_out_fog_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(1.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(action);
}
