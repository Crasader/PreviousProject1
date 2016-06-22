#ifndef __FRIEND_ROOM_H__
#define __FRIEND_ROOM_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/loading/Loading.h"
#include "game/mahjong/state/GameData.h"
#include "game/mahjong/dialog/friend/InviteCell.hpp"
USING_NS_CC;
USING_NS_CC_EXT;

class FriendRoom :public Layer, public TableViewDelegate, public TableViewDataSource{
public:
    virtual bool init();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
    void updateFriendList();
    CREATE_FUNC(FriendRoom);
private:
    EventListenerCustom* friendLsitListener2;
    InviteCell* inviters[4];
    std::vector<FriendInfo> inviteFriends;
    TableView* tableView;
    void openRoom();
    void closeView();
};
#endif