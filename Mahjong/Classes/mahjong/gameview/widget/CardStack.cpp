//
//  CardStack.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/1/19.
//
//

#include "mahjong/gameview/widget/CardStack.hpp"
#include "mahjong/jong/Jong.h"
#include "mahjong/state/GameData.h"
#include "server/MsgConfig.h"

bool CardStack::init(){
    if(!Node::init()){
        return false;
    }
    for(int i=0;i<4;i++){
        Jong* jon = Jong::create();
        jon->showJong(oppositedeal,-1,false);
        jon->setPosition(885+i*42,240);
        addChild(jon);
        jon->setOpacity(77);
        jon->runAction(FadeTo::create(6.0/24,255));
    }
    for(int j=0;j<3;j++){
        Jong* jon = Jong::create();
        jon->showJong(oppositedeal,-1,false);
        jon->setPosition(927+j*42,250);
        jon->setOpacity(77);
        jon->runAction(FadeTo::create(6.0/24,255));
        addChild(jon,2);
    }
    auto shyu = Sprite::create("gameview/shenyu.png");
    shyu->setPosition(957,198);
    shyu->setOpacity(77);
    shyu->runAction(FadeTo::create(6.0/24,255));
    addChild(shyu);
    auto alt = LabelAtlas::create(StringUtils::format("%d",0),"gameview/ju_shu_num.png",20,30,'0');
    alt->setAnchorPoint(Point::ANCHOR_MIDDLE);
    alt->setPosition(997,200);
    alt->setOpacity(77);
    alt->runAction(FadeTo::create(6.0/24,255));
    alt->setTag(911);
    addChild(alt);
    
    if(GAMEDATA::getInstance()->getMahjongRoomType() == MahjongRoom::privateRoom){
        LabelAtlas* jushu = LabelAtlas::create(StringUtils::format("%s:%s",GAMEDATA::getInstance()->getFriendOpenRoomResp().prjucount.c_str(),GAMEDATA::getInstance()->getFriendOpenRoomResp().prjushu.c_str()), "gameview/ju_shu_num.png",20,30,'0');
        jushu->setColor(Color3B(234,195,90));
        jushu->setTag(6510);
        jushu->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        jushu->setPosition(990,165);
        addChild(jushu);
        
        auto ju = Sprite::create("gameview/private_jushu.png");
        ju->setPosition(1005,160);
        addChild(ju);
    }

    return true;
}

void CardStack::setShowNum(int  num){
    if(NULL != getChildByTag(911)){
        ((LabelAtlas*)getChildByTag(911)) ->setString(StringUtils::format("%d",num));
    }
    if(NULL != getChildByTag(6510)){
        FriendOpenRoomRespData data = GAMEDATA::getInstance()->getFriendOpenRoomResp();
        ((LabelAtlas*)getChildByTag(6510)) ->setString(StringUtils::format("%s:%s",data.prjucount.c_str(),data.prjushu.c_str()));
    }

}

