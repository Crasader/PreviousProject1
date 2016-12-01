//
//  ChargeGold.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "mahjong/shop/gold/ChargeGold.hpp"
#include "mahjong/shop/ShopHintDialog.hpp"
#include "mahjong/state/GameData.h"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/loading/Loading.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/utils/ParticleUtil.hpp"
#include "server/NetworkManage.h"

bool ChargeGold::init(){
    if(!Layer::init()){
        
        return false;
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getGoldChargeListCommand());
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto dialog_bg = Sprite::create("shop/charge_bg.png");
    dialog_bg->setPosition(640,360);
    dialog_bg->setScaleX(1.2f);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/buy_gold_title.png");
    title->setPosition(654,560);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChargeGold::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1140, 550);
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
            //刷新用户信息
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
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
        propBg->setPosition(205+175*i,345);
        addChild(propBg);
        
        auto light = Sprite::create("shop/gold_bg_light.png");
        light->setPosition(205+175*i,370);
        addChild(light);
        
        auto diamond = Sprite::create();
        if(i==0){
            diamond->setTexture("shop/gold_icon_1.png");
        }else if(i==1||i==2){
            diamond->setTexture("shop/gold_icon_2.png");
        }else{
            diamond->setTexture("shop/gold_icon_3.png");
            
        }
        diamond->setPosition(205+175*i,370);
        this->addChild(diamond);
        
        auto piao = Sprite::create();
        piao->setPosition(205+175*i,280);
        addChild(piao);
        
        if(i==0){
            piao->setTexture("shop/purple_piaodai.png");
        }else if(i==1||i==2){
            piao->setTexture("shop/red_piaodai.png");
        }else{
            piao->setTexture("shop/yellow_piaodai.png");
            
        }
        
        LabelAtlas* diamondNum = LabelAtlas::create(StringUtils::format("%d",list.list.at(i).gold/10000),"shop/prop_num.png",21,28,'0');
        diamondNum->setPosition(190+175*i,291);
        diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(diamondNum);
        
        auto fontWan = Sprite::create("shop/font_wan.png");
        addChild(fontWan);
        fontWan->setPosition(200+175*i,291);
        
        auto zhuan = Sprite::create("shop/gold_text.png");
        zhuan->setPosition(245+175*i,291);
        addChild(zhuan);
        
        
        auto btnImage = MenuItemImage::create("shop/button_bg_1.png","shop/button_bg_2.png",CC_CALLBACK_1(ChargeGold::chargeGoldBtn, this));
        btnImage->setTag(list.list.at(i).gold);
        auto myMenu = Menu::create(btnImage,NULL);
        myMenu->setPosition(205+175*i,225);
        addChild(myMenu);
        
        
        
        auto yuan = Sprite::create("mjitem/fangka_icon.png");
        yuan->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(yuan);
        
        auto chen = Sprite::create("shop/cheng_hao.png");
        chen->setPosition(Point::ANCHOR_MIDDLE_LEFT);
        addChild(chen);
        
        LabelAtlas* money=LabelAtlas::create(StringUtils::format("%d",list.list.at(i).fangka),"shop/button_num.png",26,32,'0');
        
        money->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(money);
        
        int width = yuan->getContentSize().width+chen->getContentSize().width+money->getContentSize().width;
        yuan->setPosition(205+176*i-width/2,222);
        chen->setPosition(210+176*i-width/2+yuan->getContentSize().width,227);
        money->setPosition(192+176*i+width/2,227);
    }
}
