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
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    CREATE_FUNC(GameRuleDialog);
private:
    Sprite* hongZhong;
    Sprite* shangHai;
    Sprite* chongMing;
    Sprite* fanPai;
    Sprite* guizhe1;
    Sprite* guizhe2;
    Sprite* guizhe3;
    Sprite* guizhe4;
    MenuItemToggle* gzToggle;
    MenuItemToggle* pxToggle;
    MenuItemToggle* tsToggle;
    MenuItemToggle* jsToggle;
    ListView* contentView;
    int  ruleSelected = 0;
    int selcetIndex = 1;
    void closeView();
    void showJiBenGuiZhe(Ref* ref);
    void showJiBenPaiXing(Ref* ref);
    void showTeShuPaiXing(Ref* ref);
    void showYouXiJieSuan(Ref* ref);
    void updateRuleImage(int indexSelect,int index);
};
#endif /* GameRuleDialog_hpp */
