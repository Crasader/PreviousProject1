#include "mahjong/lobby/turntable/PrideCell.h"


PrideCell* PrideCell::create(PrideType propId, int propNum){
    PrideCell* bet = new PrideCell();
    if (bet&&bet->init(propId, propNum)){
        bet->autorelease();
        return bet;
    }
    else{
        delete bet;
        bet = NULL;
        return NULL;
    }
}

bool PrideCell::init(PrideType propId, int propNum){
    if (!Sprite::init()){
        return false;
    }
    setPropId(propId);
    setPropNum(propNum);
    auto prop = Sprite::create(getImageNameById(propId));
    prop->setPosition(0, 65);
    addChild(prop);
    LabelAtlas* num = LabelAtlas::create(StringUtils::format("%d", propNum), "daily/pride_num.png", 12, 22, '0');
    num->setPosition(-17, -2);
    addChild(num);
    if(propId == PrideType::fangka){
        auto zhang = Sprite::create("daily/zhang_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,10);
        addChild(zhang);
    }else  if(propId == PrideType::fee){
        auto zhang = Sprite::create("daily/yuan_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,10);
        addChild(zhang);
    }else  if(propId == PrideType::prop){
        auto zhang = Sprite::create("daily/ge_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,10);
        addChild(zhang);
    }else  if(propId == PrideType::nothing){
        num->setVisible(false);
        auto zhang = Sprite::create("daily/xie_xie.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        zhang->setPosition(-30,10);
        addChild(zhang);
    }
    return true;
}

std::string PrideCell::getImageNameById(PrideType id){
    std::string imageName;
    switch (id)
    {
        case PrideType::gold:
            imageName = "common/gold_icon.png";
            break;
        case PrideType::lequan:
            imageName = "common/lequan_icon.png";
            break;
        case PrideType::fangka:
            imageName = "common/fangka_icon.png";
            break;
        case PrideType::prop:
            imageName = "daily/iphone.png";
            break;
        case PrideType::fee:
            imageName = "daily/hongbao.png";
            break;
        default:
            imageName = "daily/nothing.png";
            break;
    }
    return imageName;
}
