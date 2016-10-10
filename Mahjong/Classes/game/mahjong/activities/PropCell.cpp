//
//  ExchangePropCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "game/mahjong/activities/PropCell.hpp"
#include "game/mahjong/activities/ActivityExchange.hpp"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"


PropCell* PropCell::create(std::string propId,int rid,std::string name,std::string status){
    
    PropCell* ret = new PropCell();
    if(ret &&ret->init(propId, rid,name,status)){
        
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool PropCell::init(std::string propId,int rid,std::string name,std::string status){
    if(!Sprite::init()){
        return false;
    }
    setPropId(propId);
    setPropRid(rid);
    setPropName(name);
    auto bg = Sprite::create("shop/shop_prop_bg.png");
    bg->setPosition(0,0);
    addChild(bg);
    
    auto light = Sprite::create("shop/prop_light.png");
    light->setPosition(0,15);
    addChild(light);
    
    
    auto cell = Sprite::create(getImageNameById(atoi(propId.c_str())));
    cell->setPosition(0,42);
    addChild(cell);
    
    auto btnImage = MenuItemImage::create("shop/btn_buy_1.png","shop/btn_buy_2.png",CC_CALLBACK_1(PropCell::confirmChange, this));
    auto menu = Menu::create(btnImage,NULL);
    menu->setPosition(0,-75);
    addChild(menu);
    
    return true;
}

void PropCell::confirmChange(Ref* ref){
//    MenuItemImage* temp = (MenuItemImage*)ref;
   //兑换
    ActivityExchange* exchange = ActivityExchange::create(getPropRid(), getPropName());
    getParent()->addChild(exchange);
}

std::string PropCell::getImageNameById(int id){
    //后期可以做成从网络获取数据,目前在客户端写死
//    HUAFEI10(1, "话费10元"),
//    HUAFEI20(2, "话费20元"),
//    HUAFEI30(3,"话费30元"),
//    HUAFEI50(4,"话费50元"),
//    HUAFEI100(5,"话费100元"),
//    LIULIANG11(10,"流量10M"),
//    LIULIANG100(11,"流量100M"),
//    IPHONE(21,"IPHONE手机");
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
