//
//  ExchangePropCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "mahjong/lobby/shop/huafei/ExchangeFangKaCell.hpp"
#include "mahjong/lobby/shop/huafei/ExchangeHuafeiItem.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"
#include "userdata/UserData.h"



ExchangeFangKaCell* ExchangeFangKaCell::create(std::string number,std::string url,std::string price){
    
    ExchangeFangKaCell* ret = new ExchangeFangKaCell();
    if(ret &&ret->init(number,url,price)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ExchangeFangKaCell::init(std::string number,std::string url,std::string price){
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
    
    auto fangkaNum = LabelAtlas::create(StringUtils::format(":%s",number.c_str()), "shop/change_gold_num.png", 22, 29, '0');
    fangkaNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangkaNum->setPosition(0,22);
    addChild(fangkaNum);
    
    
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
    
    auto btnImage = MenuItemImage::create("shop/btn_buy_1.png","shop/btn_buy_2.png",CC_CALLBACK_1(ExchangeFangKaCell::confirmChange, this));
    btnImage->setTag(atoi(price.c_str()));
    btnImage->setName(StringUtils::format("%s张房卡",number.c_str()));
    auto menu = Menu::create(btnImage,NULL);
    menu->setPosition(0,-115);
    addChild(menu);
    return true;
}


void ExchangeFangKaCell::onEnter(){
    Sprite::onEnter();
    shopPropListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(StringUtils::format("MSG_UPDATE_SHOP_PROP_IMAG_%s",getPropUrl().c_str()), [=](EventCustom* event){
       
        if(NULL != getChildByTag(1998)){
            std::string filepath = UrlImageMannger::getInstance()->loadShopImgByUrl(getPropUrl());
            ((Sprite*)getChildByTag(1998))->setTexture(filepath);
        }
    });
}


void ExchangeFangKaCell::onExit(){
    Sprite::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(shopPropListener);
}

void ExchangeFangKaCell::confirmChange(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    //判断券是否足够
    if(UserData::getInstance()->getHuafeiQuan()>=atoi(getpropPrice().c_str())){
        ExchangeHuafeiItem* item = ExchangeHuafeiItem::create(temp->getTag(),temp->getName());
        getParent()->addChild(item);
    }else{
        ShopHintDialog* dia = ShopHintDialog::create();
        dia->showImage("shop/hua_fei_not_enough.png");
        getParent()->addChild(dia,2);
    }
}
