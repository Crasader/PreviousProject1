#ifndef __SEARCH_RESULT_H__
#define __SEARCH_RESULT_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class SearchResult :public Layer, public TableViewDataSource, public TableViewDelegate{
public:
	virtual bool init();

	virtual void tableCellTouched(TableView* table, TableViewCell* cell);

	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);

    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);

	virtual ssize_t numberOfCellsInTableView(TableView *table);

	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}

	void updateResultList();
	CREATE_FUNC(SearchResult);
private:
	TableView* tableView;
	void addFriend(Ref* ref);
	void closeView();
};
#endif