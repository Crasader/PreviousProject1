//
//  ExchangeVirtualItem.hpp
//  Mahjong
//  兑换物品
//  Created by qiuzhong on 16/6/1.
//
//

#ifndef ExchangeHuafeiItem_hpp
#define ExchangeHuafeiItem_hpp
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ExchangeHuafeiItem : public Layer, public ui::EditBoxDelegate{
public:
    static ExchangeHuafeiItem* create(int propId,std::string propName);
    virtual bool init(int propId,std::string propName);
private:
    
    
    ui::EditBox* _lianXiRen;
    ui::EditBox* _shouJiHao;
    ui::EditBox* _xiangXiDiZhi;
    
    ui::EditBox* _newPhoneNumber;
    ui::EditBox* _confirmPhoneNumber;
    
    CC_SYNTHESIZE(int , itemPropId, ItemPropId);
    CC_SYNTHESIZE(std::string , propName, PropName);
    CC_SYNTHESIZE(bool, isVirtual, IsVirtual);
    
    void showVirtualItem(int propId,std::string propName);
    void confirm(Ref* ref);
    void closeView();

    virtual void editBoxEditingDidBegin(ui::EditBox* editBox);
    
    virtual void editBoxEditingDidEnd(ui::EditBox* editBox);
    
    virtual void editBoxTextChanged(ui::EditBox* editBox, const std::string& text);
    
    virtual void editBoxReturn(ui::EditBox* editBox);
};
#endif /* ExchangeItem_hpp */
