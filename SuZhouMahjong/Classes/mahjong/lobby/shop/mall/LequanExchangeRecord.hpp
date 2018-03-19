//
//  LequanExchangeRecord.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/14.
//
//

#ifndef LequanExchangeRecord_hpp
#define LequanExchangeRecord_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class LequanExchangeRecord : public Layer,public TableViewDelegate, public TableViewDataSource {
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
    CREATE_FUNC(LequanExchangeRecord);
private:
    EventListenerCustom* recordListener;
    void showLequanExchangeRecord();
    void closeView();
    std::string getPropName(std::string id);
    std::string getPropConsume(std::string id);
    std::string getImageNameById(int id);
};
#endif /* LequanExchangeRecord_hpp */
