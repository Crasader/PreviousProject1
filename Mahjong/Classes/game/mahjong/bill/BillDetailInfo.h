#ifndef __BILL_DETAIL_INFO_H__
#define __BILL_DETAIL_INFO_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class BillDetailInfo :public Layer, public TableViewDelegate, public TableViewDataSource{
public:
	virtual bool init();

	virtual void tableCellTouched(TableView* table, TableViewCell* cell);

	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);

	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);

	virtual ssize_t numberOfCellsInTableView(TableView *table);

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    
    void setPrivatePostion();

	CREATE_FUNC(BillDetailInfo);
private:
	TableView* tableView;
	void closeView();
	void updateBillDetail();
    std::vector<BillContent> sortBillInfo(std::vector<BillContent> content);
};
#endif