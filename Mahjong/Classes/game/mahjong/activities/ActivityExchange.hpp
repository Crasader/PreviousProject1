//
//  ExchangeVirtualItem.hpp
//  Mahjong
//  兑换物品
//  Created by qiuzhong on 16/6/1.
//
//

#ifndef ActivityExchange_hpp
#define ActivityExchange_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ActivityExchange : public Layer, public EditBoxDelegate{
public:
    static ActivityExchange* create(int propId,std::string propName);
    virtual bool init(int propId,std::string propName);
private:
    
    
    EditBox* _lianXiRen;
    EditBox* _shouJiHao;
    EditBox* _xiangXiDiZhi;
    
    EditBox* _newPhoneNumber;
    EditBox* _confirmPhoneNumber;
    
    CC_SYNTHESIZE(int , itemPropId, ItemPropId);
    
    void showVirtualItem(int propId,std::string propName);
    void confirm(Ref* ref);
    void closeView();

    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};
#endif /* ExchangeItem_hpp */
