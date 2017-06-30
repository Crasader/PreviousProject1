//
//  ChargeGold.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/lobby/LobbyScene.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/widget/ParticleUtil.hpp"
#include "mahjong/common/utils/Chinese.h"
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
    title->setPosition(654,555);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChargeGold::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1170, 570);
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
            da->showText(ChineseWord("dialog_text_21"));
            ParticleUtil* par = ParticleUtil::create(MyParticleType::goldOnly);
            addChild(par,2);
            //刷新用户信息
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
        }else{
			da->showText(ChineseWord("dialog_text_22"));
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
    
        
        float goldN = list.list.at(i).gold/10000;
        LabelAtlas* diamondNum = LabelAtlas::create("0","shop/change_gold_num.png",22,29,'0');
        if(goldN>=1){
            diamondNum->setString(StringUtils::format(":%d",(int)goldN));
        }else{
            std::string number = StringUtils::format("%0.1f",goldN);
            int pos  =  (int)number.find(".");
            if(pos>=0){
                number.replace(pos,1, ";");
            }
            diamondNum->setString(StringUtils::format(":%s",number.c_str()));
        }
        diamondNum->setPosition(235+175*i,340);
        diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(diamondNum);
        auto fontWan = Sprite::create("shop/font_wan.png");
        addChild(fontWan);
        fontWan->setPosition(250+175*i,340);
        
        auto xiaohao = Sprite::create("shop/xiao_hao_text.png");
        xiaohao->setPosition(205+175*i,307);
        addChild(xiaohao);
        
        auto btnImage = MenuItemImage::create("shop/buy_gold_btn_1.png","shop/buy_gold_btn_2.png",CC_CALLBACK_1(ChargeGold::chargeGoldBtn, this));
        btnImage->setTag(list.list.at(i).gold);
        auto myMenu = Menu::create(btnImage,NULL);
        myMenu->setPosition(205+175*i,225);
        addChild(myMenu);
        
        auto yuan = Sprite::create("shop/fangka_num_text.png");
        yuan->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        addChild(yuan);
        
        LabelAtlas* money=LabelAtlas::create(StringUtils::format(":%d",list.list.at(i).fangka),"shop/prop_num.png",22,34,'0');
        money->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
        addChild(money);
        
        int width = yuan->getContentSize().width+money->getContentSize().width;
        money->setPosition(175+176*i,275);
        yuan->setPosition(175+176*i,275);
    }
}
