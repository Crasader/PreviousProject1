//
//  LequanExchangeRecord.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/14.
//
//

#ifndef HuafeiExchangeRecord_hpp
#define HuafeiExchangeRecord_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HuafeiExchangeRecord : public Layer,public TableViewDelegate, public TableViewDataSource {
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
    CREATE_FUNC(HuafeiExchangeRecord);
private:
    EventListenerCustom* recordListener;
    void showLequanExchangeRecord();
    void closeView();
};
#endif /* LequanExchangeRecord_hpp */
