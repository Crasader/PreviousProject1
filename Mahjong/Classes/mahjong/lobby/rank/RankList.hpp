//
//  RankListA.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/6.
//
//

#ifndef RankList_hpp
#define RankList_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class RankList : public Layer,public TableViewDelegate, public TableViewDataSource{
public:
    bool init();
    void updateRankLayer(std::vector<PlayerRank> rank);
    CREATE_FUNC(RankList);
private:
    std::vector<PlayerRank> myRank;
    EventListenerCustom* updateRank;
    TableView* tableView1 ;
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
};


#endif /* RankListA_hpp */
