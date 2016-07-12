//
//  LequanExchangeRecord.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/14.
//
//

#include "game/mahjong/dialog/shop/LequanExchangeRecord.hpp"
#include "server/NetworkManage.h"
#include "game/mahjong/state/GameData.h"

bool LequanExchangeRecord::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_info.png");
    title->setPosition(654,660);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(LequanExchangeRecord::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 610);
    addChild(closeMenu);
    
    auto tableView = TableView::create(this, Size(765, 450));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(270, 105);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    tableView->reloadData();

    showLequanExchangeRecord();
    return true;
}


void LequanExchangeRecord::onEnter(){
    Layer::onEnter();
    recordListener = EventListenerCustom::create(MSG_PLAYER_LEQUAN_EXCHANGE_RECORD, [](EventCustom* event){
    
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(recordListener, 1);
};


void LequanExchangeRecord::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(recordListener);
};

void LequanExchangeRecord::showLequanExchangeRecord(){
   //TODO
}

void LequanExchangeRecord::closeView(){
    removeFromParent();
}

void LequanExchangeRecord::tableCellTouched(TableView* table,TableViewCell* cell){

}


Size LequanExchangeRecord::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(765, 148);
}

TableViewCell* LequanExchangeRecord::tableCellAtIndex(TableView *table, ssize_t idx){
    auto string = String::createWithFormat("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        auto recordBg = Sprite::create("shop/duihuanjilu_box.png");
        recordBg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        cell->addChild(recordBg);
    }else{
        
    }
    return cell;
}

ssize_t LequanExchangeRecord::numberOfCellsInTableView(TableView *table){
   return GAMEDATA::getInstance()->getLeChangeRecord().records.size();
}