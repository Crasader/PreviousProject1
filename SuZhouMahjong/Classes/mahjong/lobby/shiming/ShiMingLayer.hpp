//
//  ShiMingLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/3/9.
//
//

#ifndef ShiMingLayer_hpp
#define ShiMingLayer_hpp

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ShiMingLayer : public Layer , public EditBoxDelegate{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(ShiMingLayer);
private:
    ui::EditBox* _editName1;
    ui::EditBox* _editName2;
    ui::EditBox* _editName3;
    EventListenerCustom* resultListener;
    void closeView();
    void comfirmInfo();
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};
#endif /* ShiMingLayer_hpp */
