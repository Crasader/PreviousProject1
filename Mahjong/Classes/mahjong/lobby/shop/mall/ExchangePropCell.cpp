//
//  ExchangePropCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "mahjong/lobby/shop/mall/ExchangePropCell.hpp"
#include "mahjong/lobby/shop/mall/ExchangeItem.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/GameConfig.h"
#include "userdata/UserData.h"
#include "http/image/UrlImageMannger.h"


ExchangePropCell* ExchangePropCell::create(int propId,int lequanNum,std::string propName,std::string url,std::string propType){
    
    ExchangePropCell* ret = new ExchangePropCell();
   
    if(ret &&ret->init(propId, lequanNum,propName,url,propType)){
        ret->setPropType(url);
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ExchangePropCell::init(int propId,int lequanNum,std::string propName,std::string url,std::string propType){
    if(!Sprite::init()){
        return false;
    }
    setLequanNum(lequanNum);
    auto bg = Sprite::create("shop/shop_prop_bg.png");
    bg->setPosition(0,0);
    addChild(bg);
    
    auto light = Sprite::create("shop/prop_light.png");
    light->setPosition(0,15);
    addChild(light);
    
    auto cell = Sprite::create();
    cell->setTag(1998);
    std::string filepath = UrlImageMannger::getInstance()->loadHeadImgByUrl(url);
    if(IAMGE_LOADING != filepath){
        cell->setTexture(filepath);
    }
    cell->setPosition(0,42);
    addChild(cell);
    
    
    
    auto consume_lequan = Sprite::create();
    consume_lequan->setPosition(0,-50);
    addChild(consume_lequan);
    if(lequanNum == 10000){
        consume_lequan->setTexture("shop/resume_10000.png");
    }else if(lequanNum == 17000){
        consume_lequan->setTexture("shop/resume_17000.png");
    }else if(lequanNum == 34000){
        consume_lequan->setTexture("shop/resume_34000.png");
    }else if(lequanNum == 1500000){
        consume_lequan->setTexture("shop/resume_1500000.png");
    }else{
        auto lequan = Label::createWithSystemFont(ChineseWord("xioahao"),"arial",24);
        lequan->setAnchorPoint(Point::ANCHOR_MIDDLE);
        lequan->setColor(Color3B(240,228,45));
        lequan->setPosition(0,-35);
        addChild(lequan);
		auto lequanXiao = Label::createWithSystemFont(StringUtils::format("%d%s", lequanNum, ChineseWord("lequan").c_str()), "arial", 24);
        lequanXiao->setAnchorPoint(Point::ANCHOR_MIDDLE);
        lequanXiao->setColor(Color3B(240,228,45));
        lequanXiao->setPosition(0,-65);
        addChild(lequanXiao);
    }
    
    setPropType(propType);
    auto btnImage = MenuItemImage::create("shop/btn_buy_1.png","shop/btn_buy_2.png",CC_CALLBACK_1(ExchangePropCell::confirmChange, this));
    btnImage->setTag(propId);
    btnImage->setName(propName);
    auto menu = Menu::create(btnImage,NULL);
    menu->setPosition(0,-115);
    addChild(menu);
    
    return true;
}


void ExchangePropCell::onEnter(){
    Sprite::onEnter();
    shopPropListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(StringUtils::format("MSG_UPDATE_SHOP_PROP_IMAG_%s",getPropUrl().c_str()), [=](EventCustom* event){
        if(NULL != getChildByTag(1998)){
             std::string filepath = UrlImageMannger::getInstance()->loadHeadImgByUrl(getPropUrl());
            ((Sprite*)getChildByTag(1998))->setTexture(filepath);
        }
    });
}


void ExchangePropCell::onExit(){
    Sprite::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(shopPropListener);
}

void ExchangePropCell::confirmChange(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    //判断乐券是否足够
    if(UserData::getInstance()->getTicket()>=getLequanNum()){
        ExchangeItem* item = ExchangeItem::create(temp->getTag(),temp->getName(),getPropType());
        getParent()->addChild(item);
    }else{
        ShopHintDialog* dia = ShopHintDialog::create();
        dia->showImage("shop/lequanbugou.png");
        getParent()->addChild(dia,2);
    }
}
