//
//  ChargeGold.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "game/mahjong/shop/ChargeGold.hpp"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/loading/Loading.h"
#include "server/NetworkManage.h"
#include "game/utils/StringUtil.h"
#include "game/mahjong/lobby/LobbyScene.h"
#include "game/utils/ParticleUtil.hpp"

bool ChargeGold::init(){
    if(!Layer::init()){
        
        return false;
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGoldChangeListCommand());
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto dialog_bg = Sprite::create("shop/charge_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/buy_gold_title.png");
    title->setPosition(654,560);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChargeGold::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 550);
    addChild(closeMenu);
    
    if(!GAMEDATA::getInstance()->getGoldChangeList().needInit){
        Loading* lod = Loading::create(true);
        lod->setTag(1000);
        addChild(lod);
    }else{
        showChargeGold();
    }
    return true;
    
}


void ChargeGold::onEnter(){
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_GOLD_CHANGE_LIST, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        showChargeGold();
    });
    
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_GOLD_CHANGE_RESP, [=](EventCustom* event){
        if(NULL != getChildByTag(2000)){
            getChildByTag(2000)->removeFromParent();
        }
        std::string buf = static_cast<char*>(event->getUserData());
        ShopHintDialog* da = ShopHintDialog::create();
        if(buf == "1"){
            da->showText("充值成功");
            ParticleUtil* par = ParticleUtil::create(MyParticleType::goldOnly);
            addChild(par,2);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
        }else{
            da->showText("充值失败");
        }
        addChild(da);
    });
    
}

void ChargeGold::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_GOLD_CHANGE_LIST);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_GOLD_CHANGE_RESP);
}

void ChargeGold::closeView(){
    removeFromParent();
}

void ChargeGold::chargeGoldBtn(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    Loading* lod2 = Loading::create();
    lod2->setTag(2000);
    addChild(lod2);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGoldChangeCommand(StringUtil::itos(temp->getTag())));
}

void ChargeGold::showChargeGold(){
    GoldChangeList list = GAMEDATA::getInstance()->getGoldChangeList();
    for(int i=0;i<list.list.size();i++){
        auto propBg =  Sprite::create("shop/prop_bg.png");
        propBg->setPosition(285+175*i,345);
        addChild(propBg);
        
        auto light = Sprite::create("shop/gold_bg_light.png");
        light->setPosition(285+175*i,370);
        addChild(light);
        
        auto diamond = Sprite::create();
        if(i==0){
            diamond->setTexture("shop/gold_icon_1.png");
        }else if(i==1||i==2){
            diamond->setTexture("shop/gold_icon_2.png");
        }else{
            diamond->setTexture("shop/gold_icon_3.png");
            
        }
        diamond->setPosition(285+175*i,370);
        this->addChild(diamond);
        
        auto piao = Sprite::create();
        piao->setPosition(285+175*i,280);
        addChild(piao);
        
        if(i==0){
            piao->setTexture("shop/purple_piaodai.png");
        }else if(i==1||i==2){
            piao->setTexture("shop/red_piaodai.png");
        }else{
            piao->setTexture("shop/yellow_piaodai.png");
            
        }
        
        LabelAtlas* diamondNum = LabelAtlas::create(cocos2d::String::createWithFormat("%d",list.list.at(i).gold/10000)->_string,"shop/prop_num.png",21,28,'0');
        diamondNum->setPosition(270+175*i,291);
        diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(diamondNum);
        
        auto fontWan = Sprite::create("shop/font_wan.png");
        addChild(fontWan);
        fontWan->setPosition(280+175*i,291);
        
        auto zhuan = Sprite::create("shop/gold_text.png");
        zhuan->setPosition(325+175*i,291);
        addChild(zhuan);
        
        
        auto btnImage = MenuItemImage::create("shop/button_bg_1.png","shop/button_bg_2.png",CC_CALLBACK_1(ChargeGold::chargeGoldBtn, this));
        btnImage->setTag(list.list.at(i).gold);
        auto myMenu = Menu::create(btnImage,NULL);
        myMenu->setPosition(285+175*i,225);
        addChild(myMenu);
        
        LabelAtlas* money = LabelAtlas::create(cocos2d::String::createWithFormat("%d",list.list.at(i).diamond)->_string,"shop/prop_num.png",21,28,'0');
        money->setPosition(300+176*i,230);
        money->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(money);
        
        auto yuan = Sprite::create("shop/diamond_icon_2.png");
        yuan->setPosition(325+176*i,225);
        yuan->setScale(0.6f);
        addChild(yuan);
    }
}