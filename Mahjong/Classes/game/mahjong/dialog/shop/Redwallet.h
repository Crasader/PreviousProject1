#ifndef __REDWALLET_H__
#define __REDWALLET_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Redwallet :public Layer, public TableViewDelegate, public TableViewDataSource{
public :
	virtual bool init();
    void onEnter() override;
    void onExit() override;
	CREATE_FUNC(Redwallet);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}

private:
    EventListenerCustom* redWalletRespListener;
	Layer* giveRedwalletLayer;
	Layer* getRedwalletLayer;
	Layer* tishiLayer;
	EditBox* _editPwd;
    TableView* tableView;
	void drawDialog();
	void drawGiveRedwallet();
	void drawGetRedwallet();
	void drawTishiLayer();
	void giveRedwallet();
	void getRedwallet();
	void drawRedpride(Layer* layer,Point startpos);
	void closeView();
	void closeTishiView();
};
#endif