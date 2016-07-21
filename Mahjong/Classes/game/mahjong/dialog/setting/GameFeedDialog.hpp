//
//  GameFeedDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#ifndef GameFeedDialog_hpp
#define GameFeedDialog_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameFeedDialog : public Layer , public EditBoxDelegate{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(GameFeedDialog);
private:
    EventListenerCustom* feedListener;
    void closeView();
    void clickComfirm();
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);

};

#endif /* GameFeedDialog_hpp */
