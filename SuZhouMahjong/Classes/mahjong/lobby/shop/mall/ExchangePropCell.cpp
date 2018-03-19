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
    setPropType(propType);
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
    
    
    
    auto xiaohao = Sprite::create("shop/xiao_hao_text.png");
    xiaohao->setPosition(0,-25);
    addChild(xiaohao);
    
    auto yuan = Sprite::create("shop/lequan_text.png");
    yuan->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    addChild(yuan);
    
    LabelAtlas* money=LabelAtlas::create(StringUtils::format(":%d",lequanNum),"shop/prop_num.png",22,34,'0');
    money->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(money);
    
    int width2 = money->getContentSize().width + yuan->getContentSize().width;
    money->setPosition(-width2/2,-60);
    yuan->setPosition(width2/2,-60);

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
            std::string filepath = UrlImageMannger::getInstance()->loadShopImgByUrl(getPropUrl());
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
