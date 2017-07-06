//
//  RankListC.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/6.
//
//

#include "mahjong/lobby/rank/RankListC.hpp"



void RankListC::updateRankLayer(std::vector<PlayerRank> rank){
    
    
}

bool RankListC::init(){
    tableView1 = TableView::create(this, Size(460, 305));
    tableView1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView1->setDirection(ScrollView::Direction::VERTICAL);
    tableView1->setPosition(225, 120);
    tableView1->setTag(105);
    tableView1->setDelegate(this);
    tableView1->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView1);
    tableView1->reloadData();
    return true;
}

void RankListC::tableCellTouched(TableView* table, TableViewCell* cell){
    
}

Size RankListC::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(486, 92);
}


TableViewCell* RankListC::tableCellAtIndex(TableView *table, ssize_t idx){
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
    }
    return cell;
}


ssize_t RankListC::numberOfCellsInTableView(TableView *table){
    return 4;
}
