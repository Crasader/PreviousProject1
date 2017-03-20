#include "mahjong/lobby/daily/pride/PrideCell.h"


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
    LabelAtlas* num = LabelAtlas::create("0", "daily/pride/pride_num.png", 16, 24, '0');
    num->setPosition(-15, -2);
    addChild(num);
    if (propNum / 10000 >= 1){
        num->setString(StringUtils::format("%d", propNum / 10000));
        num->setPosition(-20,-2);
        auto wan = Sprite::create("daily/pride/wan.png");
        wan->setPosition(10,10);
        addChild(wan);
    }
    else{
        num->setString(StringUtils::format("%d", propNum));
    }
    if(propId == 3){
        prop->setScale(0.6f);
        auto zhang = Sprite::create("daily/zhang_text.png");
        zhang->setPosition(10,10);
        addChild(zhang);
        
    }
    return true;
}

std::string PrideCell::getImageNameById(PrideType id){
    std::string imageName;
    switch (id)
    {
        case 0:
            imageName = "mjitem/gold_iocn.png";
            break;
        case 1:
            imageName = "mjitem/lequan_icon.png";
            break;
        case 2:
            imageName = "mjitem/jifen_icon.png";
            break;
        case 3:
            imageName = "shop/fangka_image.png";
            break;
        default:
            break;
    }
    return imageName;
}
