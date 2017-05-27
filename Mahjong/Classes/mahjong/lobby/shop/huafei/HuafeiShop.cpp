//
//  LequanShop.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "mahjong/lobby/shop/huafei/HuafeiShop.hpp"
#include "mahjong/lobby/shop/huafei/ExchangeHuafeiCell.hpp"
#include "mahjong/lobby/shop/huafei/HuafeiExchangeRecord.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/StringUtil.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"


bool HuafeiShop::init(){
    if(!Layer::init()){
        
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    addChild(menu1);
    
    auto dialog_bg = Sprite::create("shop/charge_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/huafei_title.png");
    title->setPosition(654,600);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HuafeiShop::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 550);
    addChild(closeMenu);
    
    if(GAMEDATA::getInstance()->getLequanChangeList().list.size()==0){
        Loading* lod = Loading::create(true);
        lod->setTag(1000);
        addChild(lod);
    }else{
        showHuafeiShop();
    }
    return true;
}


void HuafeiShop::onEnter(){
    Layer::onEnter();
    huafeiChangeList = EventListenerCustom::create(MSG_PLAYER_HUAFEI_CHANGE_LIST, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
            showHuafeiShop();
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(huafeiChangeList, 1);
    
    huafeiChangeResp = EventListenerCustom::create(MSG_PLAYER_HUAFEI_CHANGE_RESP, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
            showHuafeiShop();
        }
        if(GAMEDATA::getInstance()->getHuafeiChangeResult().result == "1"){
            ShopHintDialog* shop = ShopHintDialog::create();
            shop->showText("兑换成功");
            addChild(shop);
            UserData::getInstance()->setHuafeiQuan(atoi(GAMEDATA::getInstance()->getHuafeiChangeResult().huafei.c_str()));
            if(NULL != getChildByTag(962)){
                ((Label*)getChildByTag(962))->setString(StringUtils::format("%0.1f",UserData::getInstance()->getHuafeiQuan()));
            }
        }else{
            ShopHintDialog* shop = ShopHintDialog::create();
            shop->showText("兑换失败");
            addChild(shop);
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(huafeiChangeResp, 1);
}

void HuafeiShop::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(huafeiChangeList);
    _eventDispatcher->removeEventListener(huafeiChangeResp);
}

void HuafeiShop::showHuafeiShop(){
    
    auto btnBg = Sprite::create("shop/record_btn_bg.png");
    btnBg->setPosition(640,510);
    addChild(btnBg);
    
    auto recordImage = MenuItemImage::create("shop/exchange_record_1.png","shop/exchange_record_1.png",CC_CALLBACK_0(HuafeiShop::showRecord, this));
    recordImage->setScale(0.7f);
    auto recordMenu = Menu::create(recordImage, NULL);
    recordMenu->setPosition(272,512);
    addChild(recordMenu);
    
    auto lequanIcon = Sprite::create("mjlobby/huafei_icon.png");
    lequanIcon->setPosition(385,508);
    addChild(lequanIcon);
    
    Label* lequanNum = Label::createWithSystemFont(StringUtils::format("%0.1f",UserData::getInstance()->getHuafeiQuan()), "arial", 30);
    lequanNum->setColor(Color3B(255,214,88));
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setTag(962);
    lequanNum->setPosition(416,512);
    addChild(lequanNum);
    
    for(int i=0;i<GAMEDATA::getInstance()->getHuafeiChangeList().list.size();i++){
        ExchangeHuafeiCell* cell = ExchangeHuafeiCell::create(GAMEDATA::getInstance()->getHuafeiChangeList().list.at(i).propId,GAMEDATA::getInstance()->getHuafeiChangeList().list.at(i).url,GAMEDATA::getInstance()->getHuafeiChangeList().list.at(i).propPrice,GAMEDATA::getInstance()->getHuafeiChangeList().list.at(i).name);
        cell->setPosition(312+(i%4)*220,315);
        addChild(cell);
    }
}


void HuafeiShop::exchange(Ref* ref){
    
    
    
}

void HuafeiShop::showRecord(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendHuafeiRecordCommmand());
    HuafeiExchangeRecord* record  = HuafeiExchangeRecord::create();
    addChild(record);
}

void  HuafeiShop:: closeView(){
    
    removeFromParent();
}
