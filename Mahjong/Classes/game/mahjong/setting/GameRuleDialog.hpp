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
USING_NS_CC;
USING_NS_CC_EXT;

class GameRuleDialog : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(GameRuleDialog);
private:
    void closeView();
};
#endif /* GameRuleDialog_hpp */
