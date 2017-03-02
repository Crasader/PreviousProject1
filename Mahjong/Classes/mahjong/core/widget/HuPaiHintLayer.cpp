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
                std::vector<std::string> huPai = StringUtil::split(heroHu.at(j).hu, ",");
                //开始绘制听牌提示界面
                auto huBg = Sprite::create("gameview/hu_hint_bg.png");
                huBg->setPosition(playerHandJongs.at(i)->getPositionX(),260);
                addChild(huBg);
                auto huText = Sprite::create("gameview/hu_pai_text.png");
                huText->setPosition(playerHandJongs.at(i)->getPositionX(),400);
                addChild(huText);
                int num =  playerHero->getNumbersByPoker(heroHu.at(j).hu);
                auto huNum = LabelAtlas::create(StringUtils::format("%d",num), "gameview/hu_pai_num.png", 12, 17, '0');
                huNum->setPosition(playerHandJongs.at(i)->getPositionX()+5,390);
                addChild(huNum);
                //绘制可以胡的牌
                for (int j=0; j<huPai.size(); j++) {
                    auto jong = Jong::create();
                    jong->setScale(0.6f);
                    jong->showJong(herohand, atoi(huPai.at(j).c_str()));
                    jong->setPosition(playerHandJongs.at(i)->getPositionX(),170+61*j);
                    addChild(jong);
                }
                //计算胡牌剩余的张数
            }
        }
    }
    return true;
}
