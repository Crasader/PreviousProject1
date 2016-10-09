//
//  LingHongbao.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#include "game/mahjong/share/LingHongbao.hpp"
#include "server/NetworkManage.h"
#include "game/mahjong/state/GameData.h"
#include "game/loading/Loading.h"
#include "game/mahjong/dialog/prompt/HintDialog.hpp"

bool LingHongbao::init(){
    if(!Layer::init()){
        
        return false;
    }
    
    showLingHongbao();
    return true;
    
}


void LingHongbao::onEnter(){
    Layer::onEnter();
    redWalletReciveListener = EventListenerCustom::create(MSG_RECIVE_RED_WALLET_INFO, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        ReciveRedWallet data = GAMEDATA::getInstance()->getReciveRedWallet();
        if(data.result == "1"){
            HintDialog* dia = HintDialog::create("红包领取成功", NULL);
            addChild(dia);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_UPDATE_HERO_INFO);
        }else if(data.result == "0"){
            HintDialog* dia = HintDialog::create("推广活动已经结束了", NULL);
            addChild(dia);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_UPDATE_HERO_INFO);
        }else if(data.result == "2"){
            HintDialog* dia = HintDialog::create("红包已经被抢完了", NULL);
            addChild(dia);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_UPDATE_HERO_INFO);
        }else if(data.result == "3"){
            HintDialog* dia = HintDialog::create("你已经领取过红包了", NULL);
            addChild(dia);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_UPDATE_HERO_INFO);
        }else if(data.result == "4"){
            HintDialog* dia = HintDialog::create("不能领取自己发的红包", NULL);
            addChild(dia);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_UPDATE_HERO_INFO);
        }
        else{
            HintDialog* dia = HintDialog::create("红包已经被抢完了", NULL);
            addChild(dia);
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(redWalletReciveListener, 1);
}

void LingHongbao::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(redWalletReciveListener);
}

void LingHongbao::showLingHongbao(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
//    auto all_bg = Sprite::create("common/all_bg.jpg");
//    all_bg->setPosition(640, 360);
//    addChild(all_bg);
//    
    auto  dialogBg = Sprite::create("shop/shop_bg_2.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(LingHongbao::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    
    auto title = Sprite::create("shop/linhongbao.png");
    title->setPosition(640,610);
    addChild(title);
    
    auto text = Sprite::create("shop/shurukoulin.png");
    text->setPosition(640,480);
    addChild(text);
    
    auto inputBg = Scale9Sprite::create("common/input_box_bg.png");
    inputBg->setContentSize(Size(450, 81));
    inputBg->setPosition(640, 360);
    addChild(inputBg);
    _editPwd  = EditBox::create(Size(445, 81), Scale9Sprite::create());
    _editPwd->setPosition(Point(720, 360));
    _editPwd->setFont("American Typewriter", 24);
    _editPwd->setInputMode(EditBox::InputMode::PHONE_NUMBER);
    _editPwd->setReturnType(EditBox::KeyboardReturnType::DONE);
    _editPwd->setTag(1);
    addChild(_editPwd);
    
    
    auto btnImage = MenuItemImage::create("shop/linqujiangquan_1.png","shop/linqujiangquan_2.png",CC_CALLBACK_0(LingHongbao::confirmHongbao, this));
    auto menu1= Menu::create(btnImage,NULL);
    menu1->setPosition(640,220);
    addChild(menu1);
    
    
}



void  LingHongbao::closeView(){
    removeFromParent();
}

void LingHongbao::confirmHongbao(){
    std::string text = _editPwd->getText();
    if(text != ""){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getReciveRedWalletCommand(text));
        Loading* lo = Loading::create();
        lo->setTag(1000);
        addChild(lo);
    }
}
