//
//  RankListA.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/6.
//
//

#include "mahjong/lobby/rank/RankList.hpp"
#include "http/image/UrlImageMannger.h"
#include "mahjong/common/widget/HeadImage.hpp"


void RankList::updateRankLayer(std::vector<PlayerRank> rank){
    myRank = rank;
    tableView1->reloadData();
}

bool RankList::init(){
    tableView1 = TableView::create(this, Size(486, 305));
    tableView1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    tableView1->setDirection(ScrollView::Direction::VERTICAL);
    tableView1->setPosition(35,205);
    tableView1->setTag(105);
    tableView1->setDelegate(this);
    tableView1->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView1);
    return true;
}

void RankList::tableCellTouched(TableView* table, TableViewCell* cell){
    
}

Size RankList::tableCellSizeForIndex(TableView *table, ssize_t idx){
    return Size(486, 88);
}


TableViewCell* RankList::tableCellAtIndex(TableView *table, ssize_t idx){
    TableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        
        auto bg = Sprite::create("mjlobby/rank_info_bg.png");
        bg->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        bg->setPosition(0,0);
        cell->addChild(bg);
        auto paiming = Sprite::create();
        paiming->setPosition(63,53);
        paiming->setTag(1024);
        cell->addChild(paiming);
        auto paiming2 = Label::createWithSystemFont(StringUtils::format("%d",(int)idx+1), "arial", 46);
        paiming2->setColor(Color3B(239,190,95));
        paiming2->setAnchorPoint(Point::ANCHOR_MIDDLE);
        paiming2->setPosition(63,53);
        paiming2->setTag(1025);
        cell->addChild(paiming2);
        if((int)idx == 0){
            paiming->setTexture("mjlobby/paiming_1.png");
            paiming2->setVisible(false);
        }else if((int)idx == 1){
            paiming->setTexture("mjlobby/paiming_2.png");
            paiming2->setVisible(false);
        }else if((int)idx == 2){
            paiming->setTexture("mjlobby/paiming_3.png");
            paiming2->setVisible(false);
        }else{
            paiming->setVisible(false);
            paiming2->setVisible(true);
        }
        
        auto head = Sprite::create("mjlobby/rank_head.png");
        head->setPosition(140,50);
        cell->addChild(head);
        
        HeadImage* image = HeadImage::create(Size(64,64));
        image->setTag(1026);
        image->setPosition(140,50);
        image->updateImageByName(myRank.at(idx).pic);
        cell->addChild(image);
        
        auto nickName = Label::createWithSystemFont(myRank.at(idx).key, "arial", 20);
        nickName->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        nickName->setPosition(180,53);
        nickName->setTag(1027);
        cell->addChild(nickName);
        
        auto ranName = Label::createWithSystemFont(myRank.at(idx).value, "arial", 22);
        ranName->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        ranName->setColor(Color3B(255,224,169));
        ranName->setPosition(180,25);
        ranName->setTag(1028);
        cell->addChild(ranName);
        
    }else{
        if((int)idx == 0){
            if(NULL != cell->getChildByTag(1024)){
                ((Sprite*)cell->getChildByTag(1024))->setVisible(true);
                 ((Sprite*)cell->getChildByTag(1024))->setTexture("mjlobby/paiming_1.png");
            }
            if(NULL != cell->getChildByTag(1025)){
                ((Label*)cell->getChildByTag(1025))->setVisible(false);
            }
        }else if((int)idx == 1){
            if(NULL != cell->getChildByTag(1024)){
                ((Sprite*)cell->getChildByTag(1024))->setVisible(true);
                ((Sprite*)cell->getChildByTag(1024))->setTexture("mjlobby/paiming_2.png");
            }
            if(NULL != cell->getChildByTag(1025)){
                ((Label*)cell->getChildByTag(1025))->setVisible(false);
            }
        }else if((int)idx == 2){
            if(NULL != cell->getChildByTag(1024)){
                ((Sprite*)cell->getChildByTag(1024))->setVisible(true);
                ((Sprite*)cell->getChildByTag(1024))->setTexture("mjlobby/paiming_3.png");
            }
            if(NULL != cell->getChildByTag(1025)){
                ((Label*)cell->getChildByTag(1025))->setVisible(false);
            }
        }else{
            if(NULL != cell->getChildByTag(1024)){
                ((Sprite*)cell->getChildByTag(1024))->setVisible(false);
            }
            if(NULL != cell->getChildByTag(1025)){
                ((Label*)cell->getChildByTag(1025))->setVisible(true);
                ((Label*)cell->getChildByTag(1025))->setString(StringUtils::format("%d",(int)idx+1));
            }
        }
        if(NULL != cell->getChildByTag(1026)){
            ((HeadImage*)cell->getChildByTag(1026))->updateImageByName(myRank.at(idx).pic);
        }
        if(NULL != cell->getChildByTag(1027)){
            ((Label*)cell->getChildByTag(1027))->setString(myRank.at(idx).key);
        }

        if(NULL != cell->getChildByTag(1028)){
            ((Label*)cell->getChildByTag(1028))->setString(myRank.at(idx).value);
        }

    }
    return cell;
}


ssize_t RankList::numberOfCellsInTableView(TableView *table){
    return myRank.size();
}
