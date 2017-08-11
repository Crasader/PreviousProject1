//
//  NoticeDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/24.
//
//

#include "mahjong/lobby/collaborate/CollaborateDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "wechat/android/CallAndroidMethod.h"



bool CollaborateDialog::init(){
    if (!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 150), 1280, 720);
    addChild(bg0);
    
    auto bg = Sprite::create();
    bg->setContentSize(Size(929,604));
    bg->setPosition(640,360);
    addChild(bg);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(CollaborateDialog::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1070,630);
    addChild(menu,10);
    
    content = Sprite::create();
    content->setPosition(640,360);
    content->setVisible(false);
    addChild(content);
    setContentImage(UserData::getInstance()->getCollaborateUrl());
    return true;
}

void CollaborateDialog::onEnter(){
    Layer::onEnter();
    updateContentImg  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_GONG_GAO_SHOW_DIALOG, [=](EventCustom* event){
        setContentImage(UserData::getInstance()->getCollaborateUrl());
    });
    
}

void CollaborateDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateContentImg);
}


void CollaborateDialog::closeView(){
    removeFromParent();
}


void CollaborateDialog::setContentImage(std::string url){
    std::string path = UrlImageMannger::getInstance()->loadNoticeImgByUrl(url);
    if(path != IAMGE_LOADING){
        content->setVisible(true);
        content->setTexture(path);
    }
}
