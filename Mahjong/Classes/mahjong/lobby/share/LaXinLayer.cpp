//
//  LaXinLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/8/15.
//
//

#include "mahjong/lobby/share/LaXinLayer.hpp"
#include "mahjong/common/state/GameData.h"
#include "userdata/UserData.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

bool LaXinLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(LaXinLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 595);
    addChild(closeMenu);
    
    auto titile = Sprite::create("share/title_yaoqinghongbao.png");
    titile->setPosition(645,582);
    addChild(titile);
    
    
    auto yaoqingtext = Label::createWithSystemFont(UserData::getInstance()->getShareTextContent(), "arial", 24);
    yaoqingtext->setWidth(700);
    yaoqingtext->setAlignment(cocos2d::TextHAlignment::CENTER);
    yaoqingtext->setPosition(640,510);
    yaoqingtext->setColor(Color3B(196,106,22));
    addChild(yaoqingtext);
    
    auto tabelViewBg = Sprite::create("share/yq_bg.png");
    tabelViewBg->setPosition(640,340);
    addChild(tabelViewBg);
    
    
    auto friendImg = MenuItemImage::create("share/share_btn_1.png", "share/share_btn_2.png",CC_CALLBACK_0(LaXinLayer::shareToFriend, this));
    auto quanImg = MenuItemImage::create("share/friend_btn_1.png", "share/friend_btn_2.png",CC_CALLBACK_0(LaXinLayer::shareToQuan, this));
    auto mymenu = Menu::create(friendImg,quanImg,NULL);
    mymenu->alignItemsHorizontallyWithPadding(30);
    mymenu->setPosition(640,165);
    addChild(mymenu);
    
    return true;
}

void LaXinLayer::closeView(){
    removeFromParent();
}

void LaXinLayer::shareToFriend(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData1().url;
    if(GAMEDATA::getInstance()->getMahjongShareData1().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().phead,GAMEDATA::getInstance()->getMahjongShareData1().pcontent,false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().phead,GAMEDATA::getInstance()->getMahjongShareData1().pcontent,0);
#endif
}


void LaXinLayer::shareToQuan(){
    std::string shareUrl = GAMEDATA::getInstance()->getMahjongShareData1().url;
    if(GAMEDATA::getInstance()->getMahjongShareData1().type == "1"){
        shareUrl = StringUtils::format("%s%s",shareUrl.c_str(),UserData::getInstance()->getPoxiaoId().c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CallAndroidMethod::getInstance()->shareToWeChat(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().head,GAMEDATA::getInstance()->getMahjongShareData1().content,true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->doWechatShareWeb(shareUrl,GAMEDATA::getInstance()->getMahjongShareData1().head,GAMEDATA::getInstance()->getMahjongShareData1().content,1);
#endif
}

ssize_t LaXinLayer::numberOfCellsInTableView(TableView *table)
{
    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
    return info.bills.size();
}
void LaXinLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    
}

Size LaXinLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(832, 138);
}

TableViewCell* LaXinLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
    BillInfoAll info = GAMEDATA::getInstance()->getBillInfoAll();
    TableViewCell *cell = table->dequeueCell();
    if (cell)
    {
        cell->removeFromParentAndCleanup(true);
        cell = nullptr;
    }
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
    }
    return cell;
}
