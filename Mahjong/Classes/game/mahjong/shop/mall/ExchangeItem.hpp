//
//  ExchangeVirtualItem.hpp
//  Mahjong
//  兑换物品
//  Created by qiuzhong on 16/6/1.
//
//

#ifndef ExchangeItem_hpp
#define ExchangeItem_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ExchangeItem : public Layer, public EditBoxDelegate{
public:
    static ExchangeItem* create(int propId,std::string propName);
    virtual bool init(int propId,std::string propName);
private:
    
    
    EditBox* _lianXiRen;
    EditBox* _shouJiHao;
    EditBox* _xiangXiDiZhi;
    
    EditBox* _newPhoneNumber;
    EditBox* _confirmPhoneNumber;
    
    CC_SYNTHESIZE(int , itemPropId, ItemPropId);
    CC_SYNTHESIZE(bool, isVirtual, IsVirtual);
    
    void showRealItem(int propId,std::string propName);
    void showVirtualItem(int propId,std::string propName);
    void confirm(Ref* ref);
    void closeView();

    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
    
    virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);
};
#endif /* ExchangeItem_hpp */
