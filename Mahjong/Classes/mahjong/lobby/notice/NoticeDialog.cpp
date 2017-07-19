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
    menu->setPosition(1080,640);
    addChild(menu,3);
    
    content = Sprite::create();
    content->setPosition(640,360);
    content->setVisible(false);
    addChild(content);
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    contentWebView = cocos2d::experimental::ui::WebView::create();
    contentWebView->setContentSize(bg->getContentSize()*0.9);
    contentWebView->setPosition(Point(640,360));
    contentWebView->setVisible(false);
    addChild(contentWebView);
#endif
    return true;
}

void NoticeDialog::onEnter(){
    Layer::onEnter();
    updateContentImg  = Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_WAN_JIA_GONG_GAO_SHOW_DIALOG, [=](EventCustom* event){
        setContentImage(GAMEDATA::getInstance()->getGameActivityData().imageUrl,GAMEDATA::getInstance()->getGameActivityData().imageUrl2,GAMEDATA::getInstance()->getGameActivityData().showTime);
    });
    
}

void NoticeDialog::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(updateContentImg);
}


void NoticeDialog::closeView(){
    removeFromParent();
}


void NoticeDialog::setContentImage(std::string url,std::string url2,std::string showTime){
    if(url2 != ""){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if(showTime == ""){
            showTime = "6";
        }
        contentWebView->setVisible(true);
        contentWebView->loadURL(url2);
//        schedule([=](float dt){
//            removeFromParent();
//        }, 0, 0, atoi(showTime.c_str()),"dismiss");
#endif
    }else{
        std::string path = UrlImageMannger::getInstance()->loadNoticeImgByUrl(url);
        if(showTime == "")
            showTime = "6";
        if(path != IAMGE_LOADING){
            content->setVisible(true);
            content->setTexture(path);
            if("" != GAMEDATA::getInstance()->getGameActivityData().jumpUrl){
                MenuItem* clickUrl = MenuItem::create([=](Ref* ref){
                    Application::getInstance()->openURL(GAMEDATA::getInstance()->getGameActivityData().jumpUrl);
                });
                clickUrl->setContentSize(content->getContentSize());
                Menu* myMenu = Menu::create(clickUrl,NULL);
                myMenu->setPosition(640,360);
                addChild(myMenu);
                if(showTime == ""){
                    showTime = "6";
                }
                schedule([=](float dt){
                    removeFromParent();
                }, 0, 0, atoi(showTime.c_str()),"dismiss");
            }
        }
    }
}
