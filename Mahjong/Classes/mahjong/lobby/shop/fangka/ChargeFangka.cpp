//
//  ChargeDiamond.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/18.
//
//

#include "mahjong/lobby/shop/fangka/ChargeFangka.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/lobby/shop/fangka/ChargeItem.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/StringUtil.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"
#include "server/NetworkManage.h"


bool ChargeFangka::init(){
    
    if(!Layer::init()){
        
        return false;
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getFangkaChargeListCommand());
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    
    auto dialog_bg = Sprite::create("common/dialog_bg.png");
    dialog_bg->setTag(1024);
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/charge_title.png");
    title->setPosition(640,580);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChargeFangka::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1015, 600);
    closeMenu->setTag(1025);
    addChild(closeMenu);
    
    if(UserData::getInstance()->isWeixinPayOpen()&&UserData::getInstance()->getUserPayWay() == "2"){
        auto label = Label::createWithSystemFont(UserData::getInstance()->getDiscountInfo(), "arial", 20);
        label->setWidth(600);
        label->setAlignment(cocos2d::TextHAlignment::CENTER);
        label->setPosition(640,155);
        label->setColor(Color3B::RED);
        addChild(label);
    }else if(UserData::getInstance()->isWeixinPayOpen()&&UserData::getInstance()->getUserPayWay() == "1"){
        auto label = Label::createWithSystemFont(UserData::getInstance()->getWeiXinPayText(), "arial", 20);
        label->setWidth(580);
        label->setAlignment(cocos2d::TextHAlignment::CENTER);
        label->setPosition(610,155);
        label->setColor(Color3B::RED);
        addChild(label);
        auto copyWxImg  = MenuItemImage::create("share/btn_share_copy_1.png", "share/btn_share_copy_2.png", CC_CALLBACK_0(ChargeFangka::copyText,this));
        copyWxImg->setScaleX(0.8f);
        auto copyMenu = Menu::create(copyWxImg,NULL);
        copyMenu->setPosition(948,145);
        addChild(copyMenu);
    }

    
    Loading* lod = Loading::create(true);
    lod->setTag(1000);
    addChild(lod);
    return true;
    
}


void ChargeFangka::onEnter(){
    Layer::onEnter();
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_GOLD_CHANGE_LIST, [=](EventCustom* event){
        if(NULL != getChildByTag(1000)){
            getChildByTag(1000)->removeFromParent();
        }
        showChargeDialog();
    });
}

void ChargeFangka::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_GOLD_CHANGE_LIST);
}

void ChargeFangka::showChargeDialog(){
    FangkaChargeList list = GAMEDATA::getInstance()->getFangkaChargeList();
    //按价格排序
    if(list.list.size()>0){
        for(int i=0; i<list.list.size()-1;i++){
            if(list.list.at(i).money>list.list.at(i+1).money){
                swap(list.list.at(i), list.list.at(i+1));
            }
        }
    }
    
    for(int i=0;i<list.list.size();i++){
        int posx = (1280-(list.list.size()-1)*230)/2;
        ChargeItem* item = ChargeItem::create(list.list.at(i).money, list.list.at(i).fangka,list.list.at(i).payId);
        item->setPosition(posx+230*i,345);
        addChild(item);
    }
}

void ChargeFangka::closeView(){
    removeFromParent();
}

void ChargeFangka::copyText(){
    std::string content =UserData::getInstance()->getWeiXinKeFu();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->copyToPasteboard(content);
#endif
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->copyToPasteboard(content);
#endif
    toast();
}

void ChargeFangka::toast(){
    auto bg = Sprite::create("common/toast_bg.png");
    bg->setAnchorPoint(Point::ANCHOR_MIDDLE);
    bg->setPosition(650,300);
    bg->setScaleX(0.2);
    addChild(bg);
    auto shui = Label::createWithSystemFont("复制成功","arial",26);
    shui->setColor(Color3B(255,183,64));
    shui->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    shui->setPosition(600,300);
    addChild(shui);
    
    bg->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        bg->setVisible(false);
    }), NULL));
    shui->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([=](){
        shui->setVisible(false);
    }), NULL));
}
