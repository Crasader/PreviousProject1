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



HuPaiHintLayer* HuPaiHintLayer::create(Vector<Jong*> playerHandJongs,std::vector<HeroHuPaiData> heroHu,PlayerHero* playerHero){
    HuPaiHintLayer* ret = new HuPaiHintLayer();
    if(ret && ret->init(playerHandJongs,heroHu,playerHero)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}


bool HuPaiHintLayer::init(Vector<Jong *> playerHandJongs, std::vector<HeroHuPaiData> heroHu,PlayerHero* playerHero){
    if(!Layer::init()){
        return false;
    }
    for (int i = 0; i < playerHandJongs.size(); i++){
        for (int j=0; j<heroHu.size(); j++) {
            if(playerHandJongs.at(i)->getJongType() == heroHu.at(j).poker){
                 playerHandJongs.at(i)->setPosition(playerHandJongs.at(i)->getPosition().x, playerHandJongs.at(i)->getPosition().y + 40);
                std::vector<std::string> huPai = StringUtil::split(heroHu.at(j).hu, ",");
                //开始绘制听牌提示界面
                auto huBg = Sprite::create("gameview/hu_hint_bg.png");
                huBg->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
                huBg->setPosition(playerHandJongs.at(i)->getPositionX(),170);
                huBg->setScale(1.0f, (20+68.0*huPai.size())/277);
                addChild(huBg);
                //绘制可以胡的牌
                for (int j=0; j<huPai.size(); j++) {
                    auto jong = Jong::create();
                    jong->setScale(0.6f);
                    huBg->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
                    jong->showJong(herohand, atoi(huPai.at(j).c_str()));
                    jong->setPosition(playerHandJongs.at(i)->getPositionX(),215+63*j);
                    addChild(jong);
                }
                auto huText = Sprite::create("gameview/hu_pai_text.png");
                huText->setPosition(playerHandJongs.at(i)->getPositionX(),195+63*huPai.size());
                addChild(huText);
                int num =  playerHero->getNumbersByPoker(heroHu.at(j).hu);
                auto huNum = LabelAtlas::create(StringUtils::format("%d",num), "gameview/hu_pai_num.png", 12, 17, '0');
                huNum->setPosition(playerHandJongs.at(i)->getPositionX()+5,180+63*huPai.size());
                addChild(huNum);
            }
        }
    }
    return true;
}
