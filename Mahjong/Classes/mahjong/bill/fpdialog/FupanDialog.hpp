//
//  FupanDialog_hpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#ifndef FupanDialog_hpp
#define FupanDialog_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define CLOSE_HINT_DIALOG "close_hint_dialog"

class FupanDialog : public Layer, public EditBoxDelegate{
public:
    bool init();
    CREATE_FUNC(FupanDialog);
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
private:
    void closeView();
};
#endif /* FupanDialog_hpp */
