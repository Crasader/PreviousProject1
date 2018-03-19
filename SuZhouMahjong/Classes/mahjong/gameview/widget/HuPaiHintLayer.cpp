//
//  HuPaiHintLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/2.
//
//

#include "mahjong/gameview/widget/HuPaiHintLayer.hpp"
#include "mahjong/gameview/suzhou/normal/SuZhouView.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/SeatIdUtil.h"



HuPaiHintLayer* HuPaiHintLayer::create(HeroHuPaiData heroHu,PlayerHero* playerHero){
    HuPaiHintLayer* ret = new HuPaiHintLayer();
    if(ret && ret->init(heroHu,playerHero)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}


bool HuPaiHintLayer::init(HeroHuPaiData heroHu,PlayerHero* playerHero){
    if(!Layer::init()){
        return false;
    }
    //开始绘制听牌提示界面
    auto huBg = ui::Scale9Sprite::create("gameview/hu_hint_bg.png");
    huBg->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    huBg->setContentSize(Size(75+heroHu.data.size()*40+(heroHu.data.size()==1?10:0),98));
    huBg->setPosition(1050,200);
    addChild(huBg);
    
    auto huText = Sprite::create("gameview/hu_pai_text.png");
    huText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huText->setPosition(5,49);
    huBg->addChild(huText);
  
    //绘制可以胡的牌
    for (int j=0; j<heroHu.data.size(); j++) {
        auto jong = Jong::create();
        jong->setScale(0.48f);
        jong->showJong(herohand, atoi(heroHu.data.at(j).poker.c_str()));
        jong->setPosition(40*j+5+65+16,60);
        huBg->addChild(jong);
        
        auto huNum = Label::createWithSystemFont(StringUtils::format("%s",heroHu.data.at(j).num.c_str()),"arial",24);
        huNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        huNum->setColor(Color3B(9,148,100));
        huNum->setPosition(40*j+5+65,15);
        huBg->addChild(huNum);
        
        auto zhang = Label::createWithSystemFont("张","arial",24);
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        zhang->setColor(Color3B(9,148,100));
        zhang->setPosition(40*j+5+65+12,15);
        huBg->addChild(zhang);
    }
    
    return true;
}
