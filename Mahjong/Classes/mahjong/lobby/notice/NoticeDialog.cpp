//
//  NoticeDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/24.
//
//

#include "mahjong/lobby/notice/NoticeDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/GameConfig.h"
#include "http/image/UrlImageMannger.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"



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
    addChild(menu,1);
    
    content = Sprite::create();
    content->setPosition(640,360);
    addChild(content);
    return true;
}

void NoticeDialog::onEnter(){
   Layer::onEnter();
    updateContentImg  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_GONG_GAO_SHOW_DIALOG, [=](EventCustom* event){
        setContentImage(GAMEDATA::getInstance()->getGameActivityData().imageUrl,GAMEDATA::getInstance()->getGameActivityData().showTime);
    });

}

void NoticeDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateContentImg);
}


void NoticeDialog::closeView(){
//    if(GAMEDATA::getInstance()->getShareActivityData().result == "1"&&!UserData::getInstance()->isClickShare()){
//        ShareActivityLayer* lau = ShareActivityLayer::create();
//        getParent()->addChild(lau,100);
//    }
    removeFromParent();
}


void NoticeDialog::setContentImage(std::string fileName,std::string showTime){
    std::string path = UrlImageMannger::getInstance()->loadNoticeImgByUrl(fileName);
    if(showTime == "")
        showTime = "6";
    if(path != IAMGE_LOADING){
        content->setTexture(path);
        if("" != GAMEDATA::getInstance()->getGameActivityData().jumpUrl){
            MenuItem* clickUrl = MenuItem::create([=](Ref* ref){
                Application::getInstance()->openURL(GAMEDATA::getInstance()->getGameActivityData().jumpUrl);
            });
            clickUrl->setContentSize(content->getContentSize());
            Menu* myMenu = Menu::create(clickUrl,NULL);
            myMenu->setPosition(640,360);
            addChild(myMenu);
        }
        schedule([=](float dt){
//            if(GAMEDATA::getInstance()->getShareActivityData().result == "1"&&!UserData::getInstance()->isClickShare()){
//                ShareActivityLayer* lau = ShareActivityLayer::create();
//                getParent()->addChild(lau,100);
//            }
            removeFromParent();
        }, 0, 0, atoi(showTime.c_str()),"dismiss");
    }
}
