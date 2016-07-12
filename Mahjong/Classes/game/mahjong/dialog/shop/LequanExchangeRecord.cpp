//
//  LequanExchangeRecord.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/14.
//
//

#include "game/mahjong/dialog/shop/LequanExchangeRecord.hpp"

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
    showLequanExchangeRecord();
    return true;
}

void LequanExchangeRecord::showLequanExchangeRecord(){
   //    duihuanjilu_box.png
}

void LequanExchangeRecord::closeView(){
    removeFromParent();
}

void LequanExchangeRecord::tableCellTouched(TableView* table,TableViewCell* cell){

}


Size LequanExchangeRecord::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(722, 132);
}

TableViewCell* LequanExchangeRecord::tableCellAtIndex(TableView *table, ssize_t idx){
    auto string = String::createWithFormat("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
    }
    return cell;
}

ssize_t LequanExchangeRecord::numberOfCellsInTableView(TableView *table){
    return 0;
}