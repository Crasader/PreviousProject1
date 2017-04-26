//
//  GameRuleDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#ifndef GameRuleDialog_hpp
#define GameRuleDialog_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/UIListView.h"
#include "ui/UIImageView.h"
#include "ui/UIRichText.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class GameRuleDialog : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(GameRuleDialog);
private:
    MenuItemToggle* qunToggle;
    MenuItemToggle* fangkaToggle;
    ListView* listView;
    ListView* listViewHz;
    void closeView();
    std::vector<std::string> getGameRulesShangHai();
    std::vector<std::string> getGameRulesHongZhong();
    void showShangHai(Ref* ref);
    void showHongZhong(Ref* ref);
};
#endif /* GameRuleDialog_hpp */
