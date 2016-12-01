#ifndef __BILL_INFO_H__
#define __BILL_INFO_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "mahjong/state/GameData.h"
USING_NS_CC;
USING_NS_CC_EXT;

class BillInfo :public Layer,public TableViewDelegate, public TableViewDataSource{
public:
	virtual bool init();
    
    void onEnter() override;
    
    void onExit() override;

	virtual void tableCellTouched(TableView* table, TableViewCell* cell);

	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);

    
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);

    
	virtual ssize_t numberOfCellsInTableView(TableView *table);

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
    
    //刷新界面
    void updateBillInfo();
    //调整显示位置
    void setShowPosition();
	CREATE_FUNC(BillInfo);
    CC_SYNTHESIZE(bool, isPrivatebill, IsPrivateBill);
private:
    EventListenerCustom* playerBillListener;
    TableView* tableView ;
	void showDetailInfo(Ref* ref);
	void closeView();
    void showKongBill();
    void screenShot();
    std::vector<BillContent> sortBillInfo(std::vector<BillContent> content);
    void afterCaptured(bool succeed, const std::string &outputFile);
};
#endif
