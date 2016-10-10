//
//  RankLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#include "game/mahjong/activities/RankLayer.hpp"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"

bool RankLayer::init(){
    if(!Layer::init()){
        return false;
    }
    drawLayerUi();
    return true;
}

void RankLayer::onEnter(){
    
    Layer::onEnter();
    rankListListener = EventListenerCustom::create(MSG_ACTIVITY_RANK_INFO, [=](EventCustom* event){
        ((Label*)getChildByTag(1001))->setString(GAMEDATA::getInstance()->getActivityRankList().weekName);
        ((Label*)getChildByTag(1002))->setString(GAMEDATA::getInstance()->getActivityRankList().weekLequan);
        tableView->reloadData();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(rankListListener, 1);
    
}

void RankLayer::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(rankListListener);
}

void RankLayer::drawLayerUi(){
    
    auto content_2 = Sprite::create("activities/act_conten_2.jpg");
    content_2->setPosition(640,290);
    addChild(content_2);
    
    auto weekName = Label::createWithSystemFont("", "arial", 24);
    weekName->setColor(Color3B::BLACK);
    weekName->setTag(1001);
    weekName->setPosition(600,450);
    addChild(weekName);
    
    auto weekLequan = Label::createWithSystemFont("", "arial", 24);
    weekLequan->setColor(Color3B::BLACK);
    weekLequan->setTag(1002);
    weekLequan->setPosition(950,450);
    addChild(weekLequan);
    
    
    tableView = TableView::create(this, Size(510, 150));
    tableView->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    tableView->setPosition(525, 145);
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    tableView->reloadData();
    
    
    
}
void RankLayer::tableCellTouched(TableView* table,TableViewCell* cell){
    
    
}


Size RankLayer::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(510, 50);
}


TableViewCell* RankLayer::tableCellAtIndex(TableView *table, ssize_t idx){
    
    TableViewCell *cell = table->dequeueCell();
    ActivityRankList ranklist = GAMEDATA::getInstance()->getActivityRankList();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        auto paiming =  Label::createWithSystemFont(StringUtils::format("%d",idx+1),"arial",30);
        paiming->setTag(101);
        paiming->setPosition(0,0);
        paiming->setColor(Color3B(219,185,71));
        paiming->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        cell->addChild(paiming);
        
        auto nickname =  Label::createWithSystemFont(StringUtils::format("%s",ranklist.rank.at(idx).nickname.c_str()),"arial",30);
        nickname->setTag(102);
        nickname->setPosition(190,0);
        nickname->setColor(Color3B(219,185,71));
        nickname->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        cell->addChild(nickname);
        
        auto lequan =  Label::createWithSystemFont(StringUtils::format("%s",ranklist.rank.at(idx).lequan.c_str()),"arial",30);
        lequan->setTag(103);
        lequan->setPosition(400,0);
        lequan->setColor(Color3B(219,185,71));
        lequan->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        cell->addChild(lequan);
        
    }else{
        if(cell->getChildByTag(101) != NULL){
            ((Label*)cell->getChildByTag(101))->setString(StringUtils::format("%d",idx+1));
        }
        if(cell->getChildByTag(102) != NULL){
            ((Label*)cell->getChildByTag(102))->setString(StringUtils::format("%s",ranklist.rank.at(idx).nickname.c_str()));
        }
        if(cell->getChildByTag(103) != NULL){
            ((Label*)cell->getChildByTag(103))->setString(StringUtils::format("%s",ranklist.rank.at(idx).lequan.c_str()));
        }
    }
    return cell;
}


ssize_t RankLayer::numberOfCellsInTableView(TableView *table){
    return GAMEDATA::getInstance()->getActivityRankList().rank.size();
}
