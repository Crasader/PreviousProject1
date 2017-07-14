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
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 100), 1280, 720);
    addChild(bg0);
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_info.png");
    title->setPosition(654,620);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HuafeiExchangeRecord::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1070, 630);
    addChild(closeMenu);
    
    auto tableView = TableView::create(this, Size(765, 470));
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
        if(GAMEDATA::getInstance()->getHuaChangeRecord().records.size()>0){
            if(NULL != getChildByTag(1001)){
                ((TableView*)getChildByTag(1001))->reloadData();
            }
        }else{
            auto bg = Sprite::create("shop/no_record_bg.png");
            bg->setPosition(640,340);
            addChild(bg);
            auto text = Sprite::create("shop/no_record_text.png");
            text->setPosition(640,360);
            addChild(text);
            
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

void HuafeiExchangeRecord::closeView(){
    removeFromParent();
}

void HuafeiExchangeRecord::tableCellTouched(TableView* table,TableViewCell* cell){
    
}


Size HuafeiExchangeRecord::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(765, 145);
}

TableViewCell* HuafeiExchangeRecord::tableCellAtIndex(TableView *table, ssize_t idx){
    auto string = StringUtils::format("%ld", idx);
    TableViewCell *cell = table->dequeueCell();
    std::string newName ="";
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        auto recordBg = Sprite::create("shop/duihuanjilu_box.png");
        recordBg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        cell->addChild(recordBg);
        
        auto content = Sprite::create();
        content->setTag(100);
        content->setPosition(20,20);
        content->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        cell->addChild(content);
        
        auto huafeiNum = LabelAtlas::create(newName, "shop/prop_num.png", 22, 34, '0');
        huafeiNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        huafeiNum->setTag(101);
        huafeiNum->setPosition(190,90);
        cell->addChild(huafeiNum);
        
        auto haufeiImage = Sprite::create("shop/chong_zhi_ka.png");
        haufeiImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        haufeiImage->setTag(98);
        haufeiImage->setPosition(huafeiNum->getContentSize().width+huafeiNum->getPositionX(),88);
        cell->addChild(haufeiImage);
        
        auto xiao = Sprite::create("shop/xiaohao_img.png");
        xiao->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        xiao->setTag(99);
        xiao->setPosition(haufeiImage->getContentSize().width+haufeiImage->getPositionX(),90);
        cell->addChild(xiao);
        
        auto huaNum = LabelAtlas::create(newName, "shop/dui_huan_num.png", 22, 32, '0');
        huaNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        huaNum->setPosition(xiao->getContentSize().width+xiao->getPositionX(),90);
        huaNum->setTag(102);
        cell->addChild(huaNum);
        
        auto quan = Sprite::create("shop/huafei_img.png");
        quan->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        quan->setTag(97);
        quan->setPosition(huaNum->getContentSize().width+huaNum->getPositionX(),90);
        cell->addChild(quan);
        
        
        auto shijian = Label::createWithSystemFont("兑换时间:","arial", 22);
        shijian->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        shijian->setColor(Color3B(133,54,33));
        shijian->setPosition(190,60);
        cell->addChild(shijian);
        
        auto time = Label::createWithSystemFont(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).time,"arial", 22);
        time->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        time->setColor(Color3B(133,54,33));
        time->setPosition(300,60);
        time->setTag(103);
        cell->addChild(time);
        
        auto shouji = Label::createWithSystemFont("兑换手机号:","arial", 22);
        shouji->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        shouji->setColor(Color3B(133,54,33));
        shouji->setPosition(190,30);
        cell->addChild(shouji);
        
        auto phoneNum = Label::createWithSystemFont(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).phone,"arial", 22);
        phoneNum->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        phoneNum->setColor(Color3B(133,54,33));
        phoneNum->setPosition(320,30);
        phoneNum->setTag(104);
        cell->addChild(phoneNum);
        
        auto stateImage = Sprite::create();
        stateImage->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        stateImage->setTag(105);
        stateImage->setPosition(600,50);
        cell->addChild(stateImage);
        if(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).state == "0"){
            stateImage->setTexture("shop/duihuanzhong.png");
        }else{
            stateImage->setTexture("shop/yiduihuan.png");
        }
    }else{
        if(NULL != cell->getChildByTag(100)){
            //            ((Sprite*)cell->getChildByTag(100))->setTexture();
        }
        if(NULL != cell->getChildByTag(101)){
            ((LabelAtlas*)cell->getChildByTag(101))->setString(newName);
        }
        if(NULL != cell->getChildByTag(102)){
            ((LabelAtlas*)cell->getChildByTag(102))->setString(newName);
        }
        if(NULL != cell->getChildByTag(103)){
            ((Label*)cell->getChildByTag(103))->setString(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).time);
        }
        if(NULL != cell->getChildByTag(104)){
            ((Label*)cell->getChildByTag(104))->setString(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).phone);
        }
        if(NULL != cell->getChildByTag(105)){
            if(GAMEDATA::getInstance()->getHuaChangeRecord().records.at(idx).state == "0"){
                ((Sprite*)cell->getChildByTag(105))->setTexture("shop/duihuanzhong.png");
            }else{
                ((Sprite*)cell->getChildByTag(105))->setTexture("shop/yiduihuan.png");
            }
        }
        if(NULL != cell->getChildByTag(98)&&NULL != cell->getChildByTag(101)){
            cell->getChildByTag(98)->setPosition(cell->getChildByTag(101)->getContentSize().width+cell->getChildByTag(101)->getPositionX(),88);
        }
        if(NULL != cell->getChildByTag(98)&&NULL != cell->getChildByTag(99)){
            cell->getChildByTag(99)->setPosition(cell->getChildByTag(98)->getContentSize().width+cell->getChildByTag(98)->getPositionX(),90);
        }
        if(NULL != cell->getChildByTag(99)&&NULL != cell->getChildByTag(102)){
            cell->getChildByTag(102)->setPosition(cell->getChildByTag(99)->getContentSize().width+cell->getChildByTag(99)->getPositionX(),90);
        }
        if(NULL != cell->getChildByTag(97)&&NULL != cell->getChildByTag(102)){
            cell->getChildByTag(97)->setPosition(cell->getChildByTag(102)->getContentSize().width+cell->getChildByTag(102)->getPositionX(),90);
        }
        
    }
    return cell;
}

ssize_t HuafeiExchangeRecord::numberOfCellsInTableView(TableView *table){
    return GAMEDATA::getInstance()->getHuaChangeRecord().records.size();
}
