//
//  AgencyResult.cpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/30.
//

#include "mahjong/lobby/agency/AgencyResult.hpp"
#include "mahjong/common/state/GameData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

bool AgencyResult::init(){
    if(!Layer::init()){
        return false;
    }
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), 1280, 720);
    addChild(bg0);
    
    auto day_bg = Sprite::create("shop/shop_bg.png");
    day_bg->setTag(1024);
    day_bg->setPosition(640, 360);
    addChild(day_bg);
    
    auto title = Sprite::create("agency/agency_title.png");
    title->setPosition(640,620);
    addChild(title);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(AgencyResult::closeView, this));
    
    auto menu =Menu::create(close,NULL);
    menu->setPosition(1070,630);
    addChild(menu,3);
    
    auto bg = Sprite::create("agency/ag_bg.png");
    bg->setPosition(640, 365);
    addChild(bg);
    
    AgencyResultList list = GAMEDATA::getInstance()->getAgencyResultList();
    
    dataLayer =  Layer::create();
    addChild(dataLayer);
    updateLayerData();
    
    auto time = Label::createWithSystemFont(StringUtils::format("日期:%s",list.time.c_str()), "arial", 26);
    time->setColor(Color3B(169,107,11));
    time->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    time->setPosition(225,590);
    addChild(time);
    
    auto name = Label::createWithSystemFont("昵称", "arial", 30);
    name->setColor(Color3B(169,107,11));
    name->setAnchorPoint(Point::ANCHOR_MIDDLE);
    name->setPosition(378,540);
    addChild(name);
    
    auto win = Label::createWithSystemFont("大赢家次数", "arial", 30);
    win->setColor(Color3B(169,107,11));
    win->setAnchorPoint(Point::ANCHOR_MIDDLE);
    win->setPosition(670,540);
    addChild(win);
    
    auto fangka = Label::createWithSystemFont("房卡", "arial", 30);
    fangka->setColor(Color3B(169,107,11));
    fangka->setAnchorPoint(Point::ANCHOR_MIDDLE);
    fangka->setPosition(950,540);
    addChild(fangka);
    
    
    
    auto shareImg = MenuItemImage::create("agency/share_btn_1.png", "agency/share_btn_2.png", CC_CALLBACK_0(AgencyResult::shareImage,this));
    auto shareMenu = Menu::create(shareImg,NULL);
    shareMenu->setPosition(640,125);
    addChild(shareMenu);
    
    auto pagedown = MenuItemImage::create("agency/page_down_1.png", "agency/page_down_2.png", CC_CALLBACK_0(AgencyResult::pageDown,this));
    auto downMenu = Menu::create(pagedown,NULL);
    downMenu->setPosition(1050,135);
    addChild(downMenu);
    
    auto pageup = MenuItemImage::create("agency/page_up_1.png", "agency/page_up_2.png", CC_CALLBACK_0(AgencyResult::pageUp,this));
    auto upMenu = Menu::create(pageup,NULL);
    upMenu->setPosition(950,135);
    addChild(upMenu);
    totalPage = (int)ceil(list.results.size()/10.0);
    pageNum = LabelAtlas::create(StringUtils::format("%d:%d",(index+1),totalPage), "agency/page_num.png", 25, 38, '0');
    pageNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
    pageNum->setPosition(998,135);
    addChild(pageNum);
    return true;
}

void AgencyResult::closeView(){
    removeFromParent();
}


void AgencyResult::pageUp(){
    if(totalPage>0){
        AgencyResultList list = GAMEDATA::getInstance()->getAgencyResultList();
        index = index - 1;
        if(index<0){
            index  = totalPage-1;
        }
        pageNum->setString(StringUtils::format("%d:%d",(index+1),totalPage));
        updateLayerData();
    }
}

void AgencyResult::pageDown(){
    if(totalPage>0){
        AgencyResultList list = GAMEDATA::getInstance()->getAgencyResultList();
        index = (index+1)%totalPage;
        pageNum->setString(StringUtils::format("%d:%d",index+1,totalPage));
        updateLayerData();
    }
}

void AgencyResult::updateLayerData(){
    dataLayer->removeAllChildren();
    AgencyResultList list = GAMEDATA::getInstance()->getAgencyResultList();
    for(int i =0; i<10; i++){
        if(index*10+i<list.results.size()){
            auto playerName = Label::createWithSystemFont(list.results.at(index*10+i).name, "arial", 26);
            playerName->setColor(Color3B(169,107,11));
            playerName->setAnchorPoint(Point::ANCHOR_MIDDLE);
            playerName->setPosition(378,500-35*i);
            dataLayer->addChild(playerName);
            
            auto playerWin = Label::createWithSystemFont(StringUtils::format("%s局",list.results.at(index*10+i).count.c_str()), "arial", 26);
            playerWin->setColor(Color3B(169,107,11));
            playerWin->setAnchorPoint(Point::ANCHOR_MIDDLE);
            playerWin->setPosition(670,500-35*i);
            dataLayer->addChild(playerWin);
            
            auto playerFangka = Label::createWithSystemFont(StringUtils::format("%s张",list.results.at(index*10+i).fangka.c_str()), "arial", 26);
            playerFangka->setColor(Color3B(169,107,11));
            playerFangka->setAnchorPoint(Point::ANCHOR_MIDDLE);
            playerFangka->setPosition(950,500-35*i);
            dataLayer->addChild(playerFangka);
        }
    }
}

void AgencyResult::shareImage(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(AgencyResult::afterCaptured, this) ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(CC_CALLBACK_2(AgencyResult::afterCaptured, this) ,path);
#endif
}

void AgencyResult::afterCaptured(bool succeed, const std::string &outputFile)
{
    if (succeed) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CallAndroidMethod::getInstance()->shareImageToWeChat(outputFile, false);
#endif
        
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CallIOSMethod::getInstance()->doWechatShareImg(outputFile, 0);
#endif
    }
}
