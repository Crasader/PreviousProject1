//
//  HuafeiChangeConfirm.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/31.
//
//

#include "mahjong/lobby/shop/huafei/HuafeiChangeConfirm.hpp"
#include "server/NetworkManage.h"


HuafeiChangeConfirm* HuafeiChangeConfirm::create(std::string propId,std::string propName, std::string phone){
    HuafeiChangeConfirm* ret = new HuafeiChangeConfirm();
    if(ret &&ret->init(propId,propName,phone)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }

}

bool HuafeiChangeConfirm::init(std::string propId,std::string propName, std::string phone){
    if(!Layer::init()){
        return false;
    }
    setItemPropId(propId);
    setPhoneNum(phone);
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto tishiBg = Sprite::create("shop/shop_bg_4.png");
    tishiBg->setPosition(640,360);
    addChild(tishiBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HuafeiChangeConfirm::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(875, 535);
    addChild(closeMenu);
    
    auto text = Label::createWithSystemFont(StringUtils::format("您兑换了%s至%s,请您仔细核对",propName.c_str(),phone.c_str()),"arial", 34);
    text->setWidth(280);
    text->setAlignment(cocos2d::TextHAlignment::CENTER);
    text->setColor(Color3B(223,162,182));
    text->setPosition(640,380);
    addChild(text);


    auto continueImage =  MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_1.png",CC_CALLBACK_0(HuafeiChangeConfirm::confirm, this));
    auto menu = Menu::create(continueImage,NULL);
    menu->setPosition(640,220);
    addChild(menu);

    return true;
}

void HuafeiChangeConfirm::confirm(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendHuafeiDuiHuanCommand(getItemPropId(),getPhoneNum()));
    removeFromParent();
}

void HuafeiChangeConfirm::closeView(){
    removeFromParent();
}
