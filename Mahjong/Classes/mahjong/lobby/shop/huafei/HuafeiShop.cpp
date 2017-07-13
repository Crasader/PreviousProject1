//
//  LequanShop.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "mahjong/lobby/shop/huafei/HuafeiShop.hpp"
#include "mahjong/lobby/shop/huafei/ExchangeHuafeiCell.hpp"
#include "mahjong/lobby/shop/huafei/ExchangeFangKaCell.hpp"
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
    
    auto dialog_bg = Sprite::create("shop/duihuan_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto yebg = Sprite::create("shop/haufei_duihuan_bg.png");
    yebg->setPosition(640,585);
    addChild(yebg);
    
    huaFeiLayer = Layer::create();
    addChild(huaFeiLayer,90);
    
    fangKaLayer = Layer::create();
    fangKaLayer->setVisible(false);
    addChild(fangKaLayer,90);
    
    auto btnImage1 = Sprite::create("shop/huafei_duihuan_btn.png");
    btnImage1->setTag(1001);
    btnImage1->setPosition(533,585);
    addChild(btnImage1);
    auto huafei_normal = MenuItemImage::create("shop/duihuan_huafei_1.png", "shop/duihuan_huafei_1.png");
    auto haufei_selected = MenuItemImage::create("shop/duihuan_huafei_2.png", "shop/duihuan_huafei_2.png");
    haufeiToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HuafeiShop::showHuaFeiChange, this), huafei_normal, haufei_selected, NULL);
    auto menu = Menu::create(haufeiToggle, NULL);
    menu->setPosition(533,585);
    addChild(menu,1);
    auto btnImage2 = Sprite::create("shop/huafei_duihuan_btn.png");
    btnImage2->setPosition(760,585);
    btnImage2->setTag(1002);
    btnImage2->setVisible(false);
    addChild(btnImage2);
    auto fangka_normal = MenuItemImage::create("shop/duihuan_fangka_1.png", "shop/duihuan_fangka_1.png");
    auto fangka_selected = MenuItemImage::create("shop/duihuan_fangka_2.png", "shop/duihuan_fangka_2.png");
    fangkaToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(HuafeiShop::showFangKaChange, this), fangka_normal, fangka_selected, NULL);
    fangkaToggle->setSelectedIndex(1);
    auto menu2 = Menu::create(fangkaToggle, NULL);
    menu2->setPosition(760,585);
    addChild(menu2,1);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HuafeiShop::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1070, 570);
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
            getParent()->addChild(shop,10);
            UserData::getInstance()->setHuafeiQuan(atof(GAMEDATA::getInstance()->getHuafeiChangeResult().huafei.c_str()));
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
    
    std::string number = StringUtils::format("%0.1f",UserData::getInstance()->getHuafeiQuan());
    int pos = number.find(".0");
    if(pos>0){
        number.replace(pos, 2, "");
    }
    Label* lequanNum = Label::createWithSystemFont(number, "arial", 30);
    lequanNum->setColor(Color3B::RED);
    lequanNum->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    lequanNum->setTag(962);
    lequanNum->setPosition(420,512);
    addChild(lequanNum);
    for(int i=0;i<GAMEDATA::getInstance()->getHuafeiChangeList().list.size();i++){
        ExchangeHuafeiCell* cell = ExchangeHuafeiCell::create(GAMEDATA::getInstance()->getHuafeiChangeList().list.at(i).tofee,GAMEDATA::getInstance()->getHuafeiChangeList().list.at(i).url,GAMEDATA::getInstance()->getHuafeiChangeList().list.at(i).fee);
        cell->setPosition(312+(i%4)*220,315);
        huaFeiLayer->addChild(cell);
    }
    
    for(int j=0;j<GAMEDATA::getInstance()->getFangkaChangeList().list.size();j++){
        ExchangeFangKaCell* cell = ExchangeFangKaCell::create(GAMEDATA::getInstance()->getFangkaChangeList().list.at(j).tofangka,GAMEDATA::getInstance()->getFangkaChangeList().list.at(j).url,GAMEDATA::getInstance()->getFangkaChangeList().list.at(j).fee);
        cell->setPosition(312+(j%4)*220,315);
        fangKaLayer->addChild(cell);
        
    }
}


void HuafeiShop::exchange(Ref* ref){
    
    
    
}


void HuafeiShop::showHuaFeiChange(Ref* ref){
    haufeiToggle->setSelectedIndex(0);
    fangkaToggle->setSelectedIndex(1);
    huaFeiLayer->setVisible(true);
    fangKaLayer->setVisible(false);
    if(NULL != getChildByTag(1001)){
        getChildByTag(1001)->setVisible(true);
    }
    if(NULL != getChildByTag(1002)){
        getChildByTag(1002)->setVisible(false);
    }
}


void HuafeiShop::showFangKaChange(Ref* ref){
    haufeiToggle->setSelectedIndex(1);
    fangkaToggle->setSelectedIndex(0);
    huaFeiLayer->setVisible(false);
    fangKaLayer->setVisible(true);
    if(NULL != getChildByTag(1001)){
        getChildByTag(1001)->setVisible(false);
    }
    if(NULL != getChildByTag(1002)){
        getChildByTag(1002)->setVisible(true);
    }
}

void HuafeiShop::showRecord(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendHuafeiRecordCommmand());
    HuafeiExchangeRecord* record  = HuafeiExchangeRecord::create();
    addChild(record,100);
}

void  HuafeiShop:: closeView(){
    
    removeFromParent();
}
