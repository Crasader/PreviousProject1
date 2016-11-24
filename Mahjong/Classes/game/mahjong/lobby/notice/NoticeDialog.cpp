//
//  NoticeDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/24.
//
//

#include "game/mahjong/lobby/notice/NoticeDialog.hpp"
#include "game/mahjong/state/GameData.h"
#include "http/image/UrlImageMannger.h"
#include "server/NetworkManage.h"
#include "game/utils/GameConfig.h"



bool NoticeDialog::init(){
    if (!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto bg = Sprite::create("shop/shop_bg.png");
    bg->setPosition(640,360);
    addChild(bg);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(NoticeDialog::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1050,610);
    addChild(menu);
    
    content = Sprite::create();
    content->setPosition(640,360);
    addChild(content);
    return true;
}

void NoticeDialog::onEnter(){
   Layer::onEnter();
    updateContentImg  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_GONG_GAO_SHOW_DIALOG, [=](EventCustom* event){
        setContentImage(GAMEDATA::getInstance()->getNoticeUrl());
    });

}

void NoticeDialog::onExit(){
    Layer::onExit();
    
}


void NoticeDialog::closeView(){
    removeFromParent();
}


void NoticeDialog::setContentImage(std::string fileName){
    std::string path = UrlImageMannger::getInstance()->loadNoticeImgByUrl(fileName);
    if(path != IAMGE_LOADING)
        content->setTexture(path);
}
