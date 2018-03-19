#include "mahjong/lobby/turntable/PrideCell.h"


PrideCell* PrideCell::create(PrideType propId, std::string propNum){
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

bool PrideCell::init(PrideType propId, std::string propNum){
    if (!Sprite::init()){
        return false;
    }
    setPropId(propId);
    setPropNum(propNum);
    auto prop = Sprite::create(getImageNameById(propId));
    prop->setPosition(0, 20);
    addChild(prop);
    std::string number = StringUtils::format("%s", propNum.c_str());
    int pos  =  (int)number.find(".");
    if(pos>=0){
        number.replace(pos,1, ":");
    }
    LabelAtlas* num = LabelAtlas::create(number,"daily/pride_num.png", 19, 28, '0');
    addChild(num);
    if(propId == PrideType::fangka){
        prop->setScale(0.7f);
        auto zhang = Sprite::create("daily/ge_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(zhang);
        num->setPosition(-((num->getContentSize().width/2+zhang->getContentSize().width/2)), 85);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,98);
    }else  if(propId == PrideType::fee){
        auto zhang = Sprite::create("daily/yuan_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(zhang);
        num->setPosition(-((num->getContentSize().width/2+zhang->getContentSize().width/2)), 85);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,98);
    }else  if(propId == PrideType::prop){
        auto zhang = Sprite::create("daily/ge_text.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(zhang);
        num->setPosition(-((num->getContentSize().width/2+zhang->getContentSize().width/2)),85);
        zhang->setPosition(num->getPositionX()+num->getContentSize().width,98);
    }else  if(propId == PrideType::nothing){
        num->setVisible(false);
        auto zhang = Sprite::create("daily/xie_xie.png");
        zhang->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//        zhang->setFlippedY(true);
        zhang->setPosition(-50,98);
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
            imageName = "daily/fangka_biaoqian.png";
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
