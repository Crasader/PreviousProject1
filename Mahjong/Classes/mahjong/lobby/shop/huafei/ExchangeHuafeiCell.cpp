//
//  ExchangePropCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "mahjong/lobby/shop/huafei/ExchangeHuafeiCell.hpp"
#include "mahjong/lobby/shop/huafei/ExchangeHuafeiItem.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"
#include "userdata/UserData.h"



ExchangeHuafeiCell* ExchangeHuafeiCell::create(std::string number,std::string url,std::string price){
    
    ExchangeHuafeiCell* ret = new ExchangeHuafeiCell();
    if(ret &&ret->init(number,url,price)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ExchangeHuafeiCell::init(std::string number,std::string url,std::string price){
    if(!Sprite::init()){
        return false;
    }
    setpropNumner(number);
    setpropPrice(price);
    setPropUrl(url);
    auto bg = Sprite::create("shop/shop_prop_bg.png");
    bg->setPosition(0,0);
    addChild(bg);
    
    auto light = Sprite::create("shop/prop_light.png");
    light->setPosition(0,15);
    addChild(light);
    
    auto cell = Sprite::create();
    cell->setTag(1998);
    std::string filepath = UrlImageMannger::getInstance()->loadShopImgByUrl(url);
    if(IAMGE_LOADING != filepath){
        cell->setTexture(filepath);
    }
    cell->setPosition(0,42);
    addChild(cell);
    
    auto consume_lequan = Sprite::create();
    consume_lequan->setPosition(0,-50);
    addChild(consume_lequan);
    auto lequan = Label::createWithSystemFont(ChineseWord("xioahao"),"arial",24);
    lequan->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lequan->setColor(Color3B::RED);
    lequan->setPosition(0,-35);
    addChild(lequan);
    auto lequanXiao = Label::createWithSystemFont(StringUtils::format("%s%s", price.c_str(), "话费券"), "arial", 24);
    lequanXiao->setAnchorPoint(Point::ANCHOR_MIDDLE);
    lequanXiao->setColor(Color3B::RED);
    lequanXiao->setPosition(0,-65);
    addChild(lequanXiao);
    
    auto btnImage = MenuItemImage::create("shop/btn_buy_1.png","shop/btn_buy_2.png",CC_CALLBACK_1(ExchangeHuafeiCell::confirmChange, this));
    btnImage->setTag(atoi(price.c_str()));
    btnImage->setName(StringUtils::format("%s元话费",number.c_str()));
    auto menu = Menu::create(btnImage,NULL);
    menu->setPosition(0,-115);
    addChild(menu);
    return true;
}


void ExchangeHuafeiCell::onEnter(){
    Sprite::onEnter();
    shopPropListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(StringUtils::format("MSG_UPDATE_SHOP_PROP_IMAG_%s",getPropUrl().c_str()), [=](EventCustom* event){
       
        if(NULL != getChildByTag(1998)){
            std::string filepath = UrlImageMannger::getInstance()->loadShopImgByUrl(getPropUrl());
            ((Sprite*)getChildByTag(1998))->setTexture(filepath);
        }
    });
}


void ExchangeHuafeiCell::onExit(){
    Sprite::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(shopPropListener);
}

void ExchangeHuafeiCell::confirmChange(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    //判断券是否足够
    if(UserData::getInstance()->getHuafeiQuan()>=atoi(getpropPrice().c_str())){
        ExchangeHuafeiItem* item = ExchangeHuafeiItem::create(temp->getTag(),temp->getName());
        getParent()->addChild(item,1000);
    }else{
        ShopHintDialog* dia = ShopHintDialog::create();
        dia->showImage("shop/hua_fei_not_enough.png");
        getParent()->addChild(dia,2);
    }
}
