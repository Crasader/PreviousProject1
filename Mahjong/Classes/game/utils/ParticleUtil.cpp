//
//  ParticleUtil.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/13.
//
//

#include "game/utils/ParticleUtil.hpp"

ParticleUtil* ParticleUtil::create(MyParticleType type){
    ParticleUtil* ret = new ParticleUtil();
    if(ret &&ret->init(type)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ParticleUtil::init(MyParticleType type)
{
    if(!Node::init()){
        return false;
    }
    if(type == MyParticleType::goldOnly){
        showGoldExplosion();
    }else if(type == MyParticleType::diamondOnly){
        showLequanExplosion();
    }else if(type == MyParticleType::lequanOnly){
        showDiamondExplosion();
    }else if(type == MyParticleType::goldAndLequan){
        showGoldAndLequanExplosion();
    }else if(type == MyParticleType::goldAndDianmond){
        showGoldAndDiamondExplosion();
    }else if(type == MyParticleType::lequanAndDiamond){
        showLequnaAndDiamondExplosion();
    }else {
        showThreeExplosion();
    }
    
    return true;
}

void ParticleUtil::showGoldExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("result/gold_1.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
}


void ParticleUtil::showLequanExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/lequan_icon.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
}

void ParticleUtil::showDiamondExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/diamond.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
}

void ParticleUtil::showGoldAndLequanExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("result/gold_1.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
    
    ParticleExplosion* effect2 = ParticleExplosion::create();
    effect2->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/lequan_icon.png"));
    effect2->setTotalParticles(1000);
    effect2->setStartColor(Color4F(255, 255, 255, 255));
    effect2->setStartColorVar(Color4F(0, 0, 0, 0));
    effect2->setEndColor(Color4F(255, 255, 255, 255));
    effect2->setEndColorVar(Color4F(0, 0, 0, 0));
    effect2->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect2->setGravity(Point(0, -400));
    effect2->setDuration(0.2f);
    effect2->setLife(2.0f);
    effect2->setSpeed(300.0f);
    effect2->setSpeedVar(20);
    effect2->setPosition(640,600);
    addChild(effect2);
}

void ParticleUtil::showGoldAndDiamondExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("result/gold_1.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
    
    ParticleExplosion* effect2 = ParticleExplosion::create();
    effect2->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/diamond.png"));
    effect2->setTotalParticles(1000);
    effect2->setStartColor(Color4F(255, 255, 255, 255));
    effect2->setStartColorVar(Color4F(0, 0, 0, 0));
    effect2->setEndColor(Color4F(255, 255, 255, 255));
    effect2->setEndColorVar(Color4F(0, 0, 0, 0));
    effect2->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect2->setGravity(Point(0, -400));
    effect2->setDuration(0.2f);
    effect2->setLife(2.0f);
    effect2->setSpeed(300.0f);
    effect2->setSpeedVar(20);
    effect2->setPosition(640,600);
    addChild(effect2);

}

void ParticleUtil::showLequnaAndDiamondExplosion(){
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/diamond.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
    
    ParticleExplosion* effect2 = ParticleExplosion::create();
    effect2->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/lequan_icon.png"));
    effect2->setTotalParticles(1000);
    effect2->setStartColor(Color4F(255, 255, 255, 255));
    effect2->setStartColorVar(Color4F(0, 0, 0, 0));
    effect2->setEndColor(Color4F(255, 255, 255, 255));
    effect2->setEndColorVar(Color4F(0, 0, 0, 0));
    effect2->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect2->setGravity(Point(0, -400));
    effect2->setDuration(0.2f);
    effect2->setLife(2.0f);
    effect2->setSpeed(300.0f);
    effect2->setSpeedVar(20);
    effect2->setPosition(640,600);
    addChild(effect2);
}

void ParticleUtil::showThreeExplosion(){
    
    ParticleExplosion* effect = ParticleExplosion::create();
    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("result/gold_1.png"));
    effect->setTotalParticles(1000);
    effect->setStartColor(Color4F(255, 255, 255, 255));
    effect->setStartColorVar(Color4F(0, 0, 0, 0));
    effect->setEndColor(Color4F(255, 255, 255, 255));
    effect->setEndColorVar(Color4F(0, 0, 0, 0));
    effect->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect->setGravity(Point(0, -400));
    effect->setDuration(0.2f);
    effect->setLife(2.0f);
    effect->setSpeed(300.0f);
    effect->setSpeedVar(20);
    effect->setPosition(640,600);
    addChild(effect);
    
    ParticleExplosion* effect2 = ParticleExplosion::create();
    effect2->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/lequan_icon.png"));
    effect2->setTotalParticles(1000);
    effect2->setStartColor(Color4F(255, 255, 255, 255));
    effect2->setStartColorVar(Color4F(0, 0, 0, 0));
    effect2->setEndColor(Color4F(255, 255, 255, 255));
    effect2->setEndColorVar(Color4F(0, 0, 0, 0));
    effect2->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect2->setGravity(Point(0, -400));
    effect2->setDuration(0.2f);
    effect2->setLife(2.0f);
    effect2->setSpeed(300.0f);
    effect2->setSpeedVar(20);
    effect2->setPosition(640,600);
    addChild(effect2);
    
    ParticleExplosion* effect3 = ParticleExplosion::create();
    effect3->setTexture(Director::getInstance()->getTextureCache()->addImage("mjitem/diamond.png"));
    effect3->setTotalParticles(1000);
    effect3->setStartColor(Color4F(255, 255, 255, 255));
    effect3->setStartColorVar(Color4F(0, 0, 0, 0));
    effect3->setEndColor(Color4F(255, 255, 255, 255));
    effect3->setEndColorVar(Color4F(0, 0, 0, 0));
    effect3->setStartSize(40.0f);	// 初始化粒子元素的尺寸
    effect3->setGravity(Point(0, -400));
    effect3->setDuration(0.2f);
    effect3->setLife(2.0f);
    effect3->setSpeed(300.0f);
    effect3->setSpeedVar(20);
    effect3->setPosition(640,600);
    addChild(effect3);
    
}