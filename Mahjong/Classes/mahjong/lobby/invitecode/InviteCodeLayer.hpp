//
//  InviteCodeLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/4.
//
//

#ifndef InviteCodeLayer_hpp
#define InviteCodeLayer_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class InviteCodeLayer : public Layer, public EditBoxDelegate{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    void showText(std::string msg);
    void showImage(std::string image);
    CREATE_FUNC(InviteCodeLayer);
private:
    ui::EditBox* _editName;
    EventListenerCustom* codeInviteResp;
    void showDialog();
    void confirm();
    void closeView();
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};

#endif /* InviteCodeLayer_hpp */
