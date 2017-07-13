//
//  HuafeiChangeConfirm.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/31.
//
//

#include "mahjong/lobby/shop/huafei/FangkaChangeConfirm.hpp"
#include "server/NetworkManage.h"


FangkaChangeConfirm* FangkaChangeConfirm::create(std::string fee){
    FangkaChangeConfirm* ret = new FangkaChangeConfirm();
    if(ret &&ret->init(fee)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }

}

bool FangkaChangeConfirm::init(std::string fee){
    if(!Layer::init()){
        return false;
    }
    setPropFee(fee);
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto tishiBg = Sprite::create("common/dialog_bg_small.png");
    tishiBg->setPosition(640,360);
    addChild(tishiBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FangkaChangeConfirm::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(885, 515);
    addChild(closeMenu);
    
    auto text = Label::createWithSystemFont(StringUtils::format("您兑换了%s张房卡到您的账号,请点击确定完成兑换",fee.c_str()),"arial", 34);
    text->setWidth(280);
    text->setAlignment(cocos2d::TextHAlignment::CENTER);
    text->setColor(Color3B::RED);
    text->setPosition(640,380);
    addChild(text);


    auto continueImage =  MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_1.png",CC_CALLBACK_0(FangkaChangeConfirm::confirm, this));
    auto menu = Menu::create(continueImage,NULL);
    menu->setPosition(640,255);
    addChild(menu);

    return true;
}

void FangkaChangeConfirm::confirm(){
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->sendDuiHuanFangkaCommand(getPropFee()));
    removeFromParent();
}

void FangkaChangeConfirm::closeView(){
    removeFromParent();
}
