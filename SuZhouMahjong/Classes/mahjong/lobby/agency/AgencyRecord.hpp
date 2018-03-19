//
//  AgencyRecord.hpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/27.
//

#ifndef AgencyRecord_hpp
#define AgencyRecord_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class AgencyRecord : public Layer,public TableViewDelegate, public TableViewDataSource{
public:
    bool init() override;
    CREATE_FUNC(AgencyRecord);
    void updateData();
private:
    TableView* recordTableView;
    void refreshRoomList();
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) override;
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(TableView *table) override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
};
#endif /* AgencyRecord_hpp */
