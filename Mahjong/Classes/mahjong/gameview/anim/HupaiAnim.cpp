//
//  HupaiAnim.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/25.
//
//

#include "mahjong/gameview/anim/HupaiAnim.hpp"
#include "mahjong/gameview/shanghai/normal/MahjongView.h"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/utils/SeatIdUtil.h"

HupaiAnim*  HupaiAnim::create(MahjongHuType hutype,int jongType,int seatId1,std::vector<int> seatId2){
    HupaiAnim* hupai = new HupaiAnim();
    if(hupai&&hupai->init(hutype,jongType,seatId1,seatId2)){
        hupai->autorelease();
        return hupai;
    }
    CC_SAFE_DELETE(hupai);
    return NULL;
}

bool HupaiAnim::init(MahjongHuType hutype,int jongType,int seatId1,std::vector<int> seatId2){
    if(!Layer::init()){
        return false;
    }
    if(seatId2.size()>0){
        for(int i=0;i<seatId2.size();i++){
            showDianpaoAnim(seatId1,seatId2.at(i),jongType);
            auto act = Sprite::create();
            addChild(act);
            act->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create([=](){
                showHuAnim(hutype,seatId2.at(i));
            }), NULL));
            
        }
    }else{
        schedule([=](float dt){
            showHuAnim(hutype,seatId1);
        }, 0, 0, 0.5f,"helle");
    }
    
    return true;
}


void HupaiAnim::showPokersLight(int seatId){
    //胡牌玩家亮牌前,光效动画
    Point pos1;
    Point pos2;
    
    Sprite* guangXiao1 = Sprite::create("result/hupai_light.png");
    guangXiao1->setOpacity(77);
    addChild(guangXiao1);
    
    Sprite* guangXiao2 = Sprite::create("result/hupai_light.png");
    addChild(guangXiao2);
    guangXiao2->setOpacity(77);
    
    
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
    
    guangXiao1->setPosition(pos1);
    guangXiao1->runAction(Sequence::create(Spawn::create(ScaleTo::create(5.0/24, scaleX,1.2f),MoveTo::create(5.0/24, pos2),
                                                         FadeTo::create(5.0/24, 200),NULL),
                                           Spawn::create(ScaleTo::create(5.0/24, 1.0f,1.0f),MoveTo::create(5.0/24, pos2), FadeTo::create(5.0/24, 0), NULL),
                                           NULL));
    
    guangXiao2->setPosition(pos2);
    guangXiao2->runAction(Sequence::create(Spawn::create(ScaleTo::create(5.0/24,scaleX,1.2f),MoveTo::create(5.0/24, pos1), FadeTo::create(5.0/24, 200),NULL),
                                           Spawn::create(ScaleTo::create(5.0/24, 1.0f,1.0f),MoveTo::create(5.0/24, pos2), FadeTo::create(5.0/24, 0),NULL),NULL));
}



void HupaiAnim::showHuAnim(MahjongHuType hutype,int seatid){
    
    auto bgLight = Sprite::create("gameview/bg_light_red.png");
    bgLight->setPosition(getPosbySeat(seatid));
    addChild(bgLight);
    bgLight->setVisible(false);
    bgLight->setVisible(0.4f);
    bgLight->setOpacity(77);
    auto spec = Sprite::create();
    spec->setPosition(getPosbySeat(seatid));
    addChild(spec);
    
    auto sequ0 =Sequence::create(DelayTime::create(5.0f/24),CallFunc::create([=](){
        bgLight->setVisible(true);
    }), Spawn::create(ScaleTo::create(2.0f/24,2.0f),FadeTo::create(2.0f/24,255), NULL), ScaleTo::create(2.0/24, 0.8f), ScaleTo::create(2.0/24, 1.0f),Repeat::create(Sequence::create(CallFunc::create([=](){
        showBgLight(spec);
    }),DelayTime::create(6.0f/24), NULL), 20),NULL);
    bgLight->runAction(sequ0);
    
    
    auto bg1 = Sprite::create("gameview/circle_ball_1.png");
    bg1->setPosition(getPosbySeat(seatid));
    addChild(bg1);
    bg1->setScale(0.25f);
    bg1->setOpacity(77);
    auto sequ1 =Sequence::create(Spawn::create(ScaleTo::create(3.0f/24,1.2),FadeTo::create(3.0f/24,255), NULL), ScaleTo::create(2.0/24, 1.0f),NULL);
    bg1->runAction(sequ1);
    
    Sprite* light1 = Sprite::create("gameview/circle_light_3.png");
    light1->setPosition(getPosbySeat(seatid));
    addChild(light1);
    light1->setScale(0.25f);
    light1->setOpacity(77);
    auto sequ2 =Sequence::create(Spawn::create(ScaleTo::create(3.0f/24,1.2),FadeTo::create(3.0f/24,255), NULL), CallFunc::create([=](){
        light1->setTexture("gameview/circle_light_1.png");
    }),ScaleTo::create(2.0/24, 1.0f),CallFunc::create([=](){
        light1->setTexture("gameview/circle_light_2.png");
    }),Repeat::create(Sequence::create(CallFunc::create([=](){
        showLightAnim(light1);
    }), DelayTime::create(3.0/24), NULL), 20), NULL);
    light1->runAction(sequ2);
    
    Sprite* bg2 = Sprite::create("gameview/purple_bg.png");
    bg2->setPosition(getPosbySeat(seatid));
    addChild(bg2);
    bg2->setVisible(false);
    bg2->setScale(0.5f);
    bg2->setOpacity(77);
    auto sequ3 =Sequence::create(DelayTime::create(7.0f/24),CallFunc::create([=](){
        bg2->setVisible(true);
    }), Spawn::create(ScaleTo::create(4.0f/24,1.0),FadeTo::create(3.0f/24,255), NULL),NULL);
    bg2->runAction(sequ3);
    
    
    if(hutype == MahjongHuType::gangkaiHu){
        auto gang = Sprite::create("gameview/gang_kai.png");
        gang->setPosition(getPosbySeat(seatid).x+15,getPosbySeat(seatid).y);
        addChild(gang);
        gang->setVisible(false);
        gang->runAction(Sequence::create(DelayTime::create(2.0/24),CallFunc::create([=](){
            gang->setVisible(true);
        }),Spawn::create(ScaleTo::create(2.0f/24,0.6f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
            showPokersLight(seatid);
            if(!GAMEDATA::getInstance()->getIsFuPan())
                ((MahjongView*)getParent())->showHandPokerOver(seatid);
        }), ScaleTo::create(2.0/24, 1.5f),ScaleTo::create(2.0/24, 1.0f), NULL));
        
        auto kai = Sprite::create("gameview/gang_kai2.png");
        kai->setPosition(getPosbySeat(seatid).x-15,getPosbySeat(seatid).y);
        addChild(kai);
        kai->setVisible(false);
        kai->runAction(Sequence::create(DelayTime::create(5.0/24),CallFunc::create([=](){
            kai->setVisible(true);
        }),Spawn::create(ScaleTo::create(2.0f/24,0.6f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
            showPokersLight(seatid);
            if(!GAMEDATA::getInstance()->getIsFuPan())
                ((MahjongView*)getParent())->showHandPokerOver(seatid);
        }), ScaleTo::create(2.0/24, 1.5f),ScaleTo::create(2.0/24, 1.0f), NULL));
        
    }else if(hutype == MahjongHuType::qianggangHu){
        auto gang = Sprite::create("gameview/qg_font_qiang.png");
        gang->setPosition(getPosbySeat(seatid).x+20,getPosbySeat(seatid).y);
        addChild(gang);
        gang->setVisible(false);
        gang->runAction(Sequence::create(DelayTime::create(2.0/24),CallFunc::create([=](){
            gang->setVisible(true);
        }),Spawn::create(ScaleTo::create(2.0f/24,0.6f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
            showPokersLight(seatid);
            if(!GAMEDATA::getInstance()->getIsFuPan())
                ((MahjongView*)getParent())->showHandPokerOver(seatid);
        }), ScaleTo::create(2.0/24, 1.5f),ScaleTo::create(2.0/24, 1.0f), NULL));
        
        auto kai = Sprite::create("gameview/qg_font_gang.png");
        kai->setPosition(getPosbySeat(seatid).x-20,getPosbySeat(seatid).y);
        addChild(kai);
        kai->setVisible(false);
        kai->runAction(Sequence::create(DelayTime::create(5.0/24),CallFunc::create([=](){
            kai->setVisible(true);
        }),Spawn::create(ScaleTo::create(2.0f/24,0.6f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
            showPokersLight(seatid);
            if(!GAMEDATA::getInstance()->getIsFuPan())
                ((MahjongView*)getParent())->showHandPokerOver(seatid);
        }), ScaleTo::create(2.0/24, 1.5f),ScaleTo::create(2.0/24, 1.0f), NULL));
        
    }else if(hutype == MahjongHuType::zimoHu){
        auto fontZi = Sprite::create("gameview/font_zi.png");
        fontZi->setPosition(getPosbySeat(seatid));
        fontZi->setVisible(false);
        fontZi->setScale(1.6f);
        fontZi->setOpacity(80);
        addChild(fontZi,1);
        fontZi->runAction(Sequence::create(DelayTime::create(2.0/24),CallFunc::create([=](){
            fontZi->setVisible(true);
        }),Spawn::create(ScaleTo::create(2.0f/24,0.6f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
            showPokersLight(seatid);
            if(!GAMEDATA::getInstance()->getIsFuPan())
                ((MahjongView*)getParent())->showHandPokerOver(seatid);
        }), ScaleTo::create(2.0/24, 1.5f),ScaleTo::create(2.0/24, 1.0f), NULL));
        
        
        auto fontMo = Sprite::create("gameview/font_mo.png");
        fontMo->setPosition(getPosbySeat(seatid));
        fontMo->setVisible(false);
        fontMo->setScale(1.6f);
        fontMo->setOpacity(80);
        addChild(fontMo,1);
        fontMo->runAction(Sequence::create(DelayTime::create(5.0/24),CallFunc::create([=](){
            fontMo->setVisible(true);
        }),Spawn::create(ScaleTo::create(2.0f/24,0.6f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
            showPokersLight(seatid);
            if(!GAMEDATA::getInstance()->getIsFuPan())
                ((MahjongView*)getParent())->showHandPokerOver(seatid);
        }), ScaleTo::create(2.0/24, 1.5f),ScaleTo::create(2.0/24, 1.0f), NULL));
        
    }else if(hutype == MahjongHuType::putongHu){
        auto huText = Sprite::create("gameview/font_hu.png");
        huText->setPosition(getPosbySeat(seatid));
        addChild(huText);
        huText->setOpacity(77);
        huText->setScale(2.2);
        auto sequ4 =Sequence::create(Spawn::create(ScaleTo::create(2.0f/24,0.6f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
            showPokersLight(seatid);
            if(!GAMEDATA::getInstance()->getIsFuPan())
                ((MahjongView*)getParent())->showHandPokerOver(seatid);
        }), ScaleTo::create(2.0/24, 1.5f),ScaleTo::create(2.0/24, 1.0f), NULL);
        huText->runAction(sequ4);
    }
    
    auto remove = Sprite::create();
    addChild(remove);
    remove->runAction(Sequence::create(DelayTime::create(60.0/24),CallFunc::create([=](){
        this->removeFromParent();
    }), NULL));
    
    
}


void HupaiAnim::showDianpaoAnim(int seatId1,int seatId2,int jongTyep ){
    
    Sprite* lighting = Sprite::create("gameview/lighting_1.png");
    lighting->setPosition(getPosbySeat(seatId1));
    addChild(lighting);
    lighting->setOpacity(77);
    lighting->setScale(2.0f);
    lighting->runAction(Sequence::create(Spawn::create(ScaleTo::create(2.0f/24,1.0f),FadeTo::create(2.0f/24,255), NULL),CallFunc::create([=](){
        showLighting(lighting);
    }), NULL));
    Jong* jong = Jong::create();
    jong->setPosition(getPosbySeat(seatId1));
    jong->showJong(herohand,jongTyep);
    addChild(jong);
    jong->setVisible(false);
    jong->runAction(Sequence::create(DelayTime::create(5.0f/24),CallFunc::create([=](){
        jong->setVisible(true);
    }),DelayTime::create(10.0f/24),MoveTo::create(5.0f/24, getPosbySeat(seatId2)),CallFunc::create([=](){
        jong->setVisible(false);
    }), NULL));
    
}


Point HupaiAnim :: getPosbySeat(int seatId){
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


void HupaiAnim::showLightAnim(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<4;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/circle_light_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(2.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));
    
}

void HupaiAnim::showBgLight(Sprite* sprite){
    auto animation = Animation::create();
    for( int i=1;i<4;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/bg_light_yellow_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(2.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    sprite->runAction(Sequence::create(action, NULL));
}

void HupaiAnim::showLighting(Sprite* lighting){
    auto animation = Animation::create();
    for( int i=1;i<9;i++)
    {
        std::string imageName = cocos2d::String::createWithFormat("gameview/lighting_%d.png",i)->_string;
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(2.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    lighting->runAction(Sequence::create(action,CallFunc::create([=](){
        lighting->setVisible(false);
    }), NULL));
}
