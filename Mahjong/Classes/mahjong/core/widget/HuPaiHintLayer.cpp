//
//  HuPaiHintLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/2.
//
//

#include "mahjong/core/widget/HuPaiHintLayer.hpp"
#include "mahjong/core/normal/MahjongView.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/utils/SeatIdUtil.h"



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
    std::vector<std::string> huPai = StringUtil::split(heroHu.hu, ",");
    //开始绘制听牌提示界面
    auto huBg = ui::Scale9Sprite::create("gameview/hu_hint_bg.png");
    huBg->setContentSize(Size(100+huPai.size()*70,172));
    huBg->setPosition(640,380);
    addChild(huBg);
    
    auto huText = Sprite::create("gameview/hu_pai_text.png");
    huText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    huText->setPosition(640-(85+huPai.size()*70)/2+5,380);
    addChild(huText);
    
    int num =  playerHero->getNumbersByPoker(heroHu.hu);
    auto huNum = LabelAtlas::create(StringUtils::format("%d",num), "gameview/hu_pai_num.png", 16, 24, '0');
    huNum->setPosition(640-(85+huPai.size()*70)/2+30,332);
    addChild(huNum);
    
    //绘制可以胡的牌
    for (int j=0; j<huPai.size(); j++) {
        auto jong = Jong::create();
        jong->setScale(0.7f);
        huBg->setAnchorPoint(Point::ANCHOR_MIDDLE);
        jong->showJong(herohand, atoi(huPai.at(j).c_str()));
        jong->setPosition(640-(85+huPai.size()*70)/2+120+70*j,380);
        addChild(jong);
    }
    
    return true;
}
