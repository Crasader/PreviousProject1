//
//  ExchangePropCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "game/mahjong/dialog/shop/ExchangePropCell.hpp"
#include "game/mahjong/dialog/shop/ExchangeItem.hpp"


ExchangePropCell* ExchangePropCell::create(int propId,int lequanNum,std::string propName){
    
    ExchangePropCell* ret = new ExchangePropCell();
    if(ret &&ret->init(propId, lequanNum,propName)){
        
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ExchangePropCell::init(int propId,int lequanNum,std::string propName){
    if(!Sprite::init()){
        return false;
    }
    
    auto bg = Sprite::create("shop/shop_prop_bg.png");
    bg->setPosition(0,0);
    addChild(bg);
    
    auto light = Sprite::create("shop/prop_light.png");
    light->setPosition(0,15);
    addChild(light);
    
    auto cell = Sprite::create(getImageNameById(propId));
    cell->setPosition(0,42);
    addChild(cell);
    
    auto lequan = Label::create("消耗"+cocos2d::String::createWithFormat("%d",lequanNum)->_string+"乐券","arial",20);
    lequan->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lequan->setColor(Color3B(240,228,45));
    lequan->setPosition(0,-25);
    addChild(lequan);
    
    auto btnImage = MenuItemImage::create("shop/btn_buy_1.png","shop/btn_buy_2.png",CC_CALLBACK_1(ExchangePropCell::confirmChange, this));
    btnImage->setTag(propId);
    btnImage->setName(propName);
    auto menu = Menu::create(btnImage,NULL);
    menu->setPosition(0,-75);
    addChild(menu);
    
    return true;
}

void ExchangePropCell::confirmChange(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    ExchangeItem* item = ExchangeItem::create(temp->getTag(),temp->getName());
    getParent()->addChild(item);
}

std::string ExchangePropCell::getImageNameById(int id){
    //后期可以做成从网络获取数据,目前在客户端写死
    switch (id) {
        case 1:
            return "shop/huafei_30.png";
        case 2:
            return "shop/huafei_30.png";
        case 3:
            return "shop/huafei_30.png";
        case 4:
            return "shop/huafei_30.png";
        case 5:
            return "shop/huafei_100.png";
        case 6:
            return "shop/huafei_50.png";
        case 7:
            return "shop/huafei_50.png";
        case 11:
            return "shop/liuliang_50.png";
        case 21:
            return "shop/ipones_6s.png";
        default:
            return "shop/huafei_30.png";
    }
    
}
