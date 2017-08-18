//
//  HuPaiHintLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/2.
//
//

#include "mahjong/gameview/widget/HuPaiHintLayer.hpp"
#include "mahjong/gameview/shanghai/normal/MahjongView.h"
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
    huBg->setContentSize(Size(102+heroHu.data.size()*72+(heroHu.data.size()==1?20:0),152));
    huBg->setPosition(640,380);
    addChild(huBg);
    
    auto huText = Sprite::create("gameview/hu_pai_text.png");
    huText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huText->setPosition(640-(102+heroHu.data.size()*70)/2,392);
    addChild(huText);
    

    
    //绘制可以胡的牌
    for (int j=0; j<heroHu.data.size(); j++) {
        auto jong = Jong::create();
        jong->setScale(0.7f);
        huBg->setAnchorPoint(Point::ANCHOR_MIDDLE);
        jong->showJong(herohand, atoi(heroHu.data.at(j).poker.c_str()));
        jong->setPosition(640-(102+heroHu.data.size()*70)/2+130+70*j,392);
        addChild(jong);
        
        auto huNum = LabelAtlas::create(StringUtils::format("%s",heroHu.data.at(j).num.c_str()),"gameview/hu_pai_num.png", 16, 24, '0');
        huNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
        huNum->setPosition(640-(102+heroHu.data.size()*70)/2+120+70*j,332);
        addChild(huNum);
        
        auto zhang = Sprite::create("gameview/hu_pai_text2.png");
        zhang->setPosition(640-(102+heroHu.data.size()*70)/2+140+70*j,332);
        addChild(zhang);
    }
    
    return true;
}
