//
//  LequanExchangeRecord.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/14.
//
//

#include "mahjong/lobby/shop/huafei/HuafeiExchangeRecord.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/Chinese.h"
#include "server/NetworkManage.h"

bool HuafeiExchangeRecord::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
        
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_info.png");
    title->setPosition(654,660);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HuafeiExchangeRecord::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 610);
    addChild(closeMenu);
    
    auto tableView = TableView::create(this, Size(765, 450));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(270, 105);
    tableView->setTag(1001);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    return true;
}


void HuafeiExchangeRecord::onEnter(){
    Layer::onEnter();
    recordListener = EventListenerCustom::create(MSG_PLAYER_HAUFEI_EXCHANGE_RECORD, [=](EventCustom* event){
        if(NULL != getChildByTag(1001)){
            ((TableView*)getChildByTag(1001))->reloadData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(recordListener, 1);
};


void HuafeiExchangeRecord::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(recordListener);
};

void HuafeiExchangeRecord::showLequanExchangeRecord(){
   //TODO
}

std::string HuafeiExchangeRecord::getPropName(std::string id){
    vector<HuafeiChange> list = GAMEDATA::getInstance()->getHuafeiChangeList().list;
    for(auto var:list){
        if(id == var.propId){
            return var.name;
        }
    }
    return "";
}


std::string HuafeiExchangeRecord::getPropConsume(std::string id){
    vector<HuafeiChange> list = GAMEDATA::getInstance()->getHuafeiChangeList().list;
    for(auto var:list){
        if(id == var.propId){
            return var.propPrice;
        }
    }
    return "";
}

void HuafeiExchangeRecord::closeView(){
    removeFromParent();
}

void HuafeiExchangeRecord::tableCellTouched(TableView* table,TableViewCell* cell){

}


Size HuafeiExchangeRecord::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(765, 148);
}

TableViewCell* HuafeiExchangeRecord::tableCellAtIndex(TableView *table, ssize_t idx){
    auto string = StringUtils::format("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        auto recordBg = Sprite::create("shop/duihuanjilu_box.png");
        recordBg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        cell->addChild(recordBg);
        
        auto content = Sprite::create(getImageNameById(atoi(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).propId.c_str())));
        content->setTag(100);
        content->setPosition(20,20);
        content->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        cell->addChild(content);
        
        auto propName = Label::createWithSystemFont(getPropName(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).propId),"Arial",20);
        propName->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        propName->setTag(101);
        propName->setPosition(200,80);
        cell->addChild(propName);
        
		auto propConfuse = Label::createWithSystemFont(ChineseWord("xioahao") + getPropConsume(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).propId) + ChineseWord("lequan"), "Arial", 20);
        propConfuse->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        propConfuse->setTag(102);
        propConfuse->setPosition(200,50);
        cell->addChild(propConfuse);
        
        
        auto stateImage = Sprite::create();
        stateImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        stateImage->setTag(103);
        stateImage->setPosition(550,50);
        cell->addChild(stateImage);
        if(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).state == "0"){
            stateImage->setTexture("shop/duihuanzhong.png");
        }else{
            stateImage->setTexture("shop/yiduihuan.png");
        }
    }else{
        
    }
    return cell;
}

ssize_t HuafeiExchangeRecord::numberOfCellsInTableView(TableView *table){
   return GAMEDATA::getInstance()->getHuaChangeRecord().records.size();
}


std::string HuafeiExchangeRecord::getImageNameById(int id){
    //后期可以做成从网络获取数据,目前在客户端写死
    switch (id) {
        case 1:
            return "shop/huafei_30.png";
        case 2:
            return "shop/huafei_30.png";
        case 3:
            return "shop/huafei_30.png";
        case 4:
            return "shop/huafei_50.png";
        case 5:
            return "shop/huafei_100.png";
        case 6:
            return "shop/huafei_200.png";
        case 21:
            return "shop/ipones_6s.png";
        default:
            return "shop/huafei_30.png";
    }
    
}
