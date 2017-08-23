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
#include "wechat/android/CallAndroidMethod.h"



bool NoticeDialog::init(){
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
                                       CC_CALLBACK_0(NoticeDialog::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1070,630);
    addChild(menu,10);
    
    content = Sprite::create();
    content->setPosition(640,360);
    content->setVisible(false);
    addChild(content);
    
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
    float localVer = atof(UserData::getInstance()->getAppVer().c_str());
    float serverVer =  atof(UserData::getInstance()->getServerAppVersion().c_str());
    if(serverVer>localVer){
        //新版本链接
        if(url2!= ""){
            std::string path = UrlImageMannger::getInstance()->loadNoticeImgByUrl(url2);
            if(path != IAMGE_LOADING){
                content->setVisible(true);
                content->setTexture(path);
            }
            auto cilckMenu = MenuItem::create(CC_CALLBACK_0(NoticeDialog::download, this));
            cilckMenu->setContentSize(Size(920,600));
            auto downMenu = Menu::create(cilckMenu,NULL);
            downMenu->setPosition(640,360);
            addChild(downMenu,2);
        }
    }else{
        if(url != ""){
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
}

//true 参数1大于参数2
//bool NoticeDialog::compareVersion(std::string max,std::string min){
//    std::vector<std::string> maxs = StringCompare
//}

void NoticeDialog::download(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(GAMEDATA::getInstance()->getGameActivityData().downLoadUrlAndroid != ""){
        CallAndroidMethod::getInstance()->downLoadAndroidApk(GAMEDATA::getInstance()->getGameActivityData().downLoadUrlAndroid);
    }
#else
    Application::getInstance()->openURL(GAMEDATA::getInstance()->getGameActivityData().downLoadUrlIOS);
#endif
}
