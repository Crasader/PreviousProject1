#ifndef __FRIEND_ADD_H__
#define __FRIEND_ADD_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class FriendListView : public Layer, public TableViewDelegate, public TableViewDataSource{
public:
	virtual bool init();
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void tableCellTouched(TableView* table,TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
	void updateFriendList();
	CREATE_FUNC(FriendListView);
    
private:
    EventListenerCustom* friendLsitListener;
    EventListenerCustom* updateLsitListener;
	TableView* tableView;
	void addConfirm();
	void chatFriend(Ref* ref);
	void viewFriend(Ref* ref);
	void deleteFriend(Ref* ref);
	void closeView();
};
#endif