//
//  AgencyRoom.hpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/27.
//

#ifndef AgencyRoom_hpp
#define AgencyRoom_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class AgencyRoom : public Layer,public TableViewDelegate, public TableViewDataSource{
public:
    bool init() override;
    CREATE_FUNC(AgencyRoom);
    void updateData();
private:
    TableView* roomTableView;
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx) override;
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(TableView *table) override;
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    void dissolveRoom(Ref* ref);
    void inviteRoom(Ref* ref);
    void refreshRoomList();
};
#endif /* AgencyRoom_hpp */
