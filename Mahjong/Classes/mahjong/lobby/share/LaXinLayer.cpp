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
    yaoqingtext->setPosition(640,500);
    yaoqingtext->setColor(Color3B(196,106,22));
    addChild(yaoqingtext);
    
    
    return true;
}

void LaXinLayer::closeView(){
    removeFromParent();
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
