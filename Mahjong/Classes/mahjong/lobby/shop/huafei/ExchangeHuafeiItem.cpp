//
//  ExchangeItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/1.
//
//

#include "mahjong/lobby/shop/huafei/ExchangeHuafeiItem.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/StringUtil.h"
#include "server/NetworkManage.h"
#include "mahjong/common/utils/Chinese.h"
#include "mahjong/lobby/shop/huafei/HuafeiChangeConfirm.hpp"


ExchangeHuafeiItem* ExchangeHuafeiItem::create(int propId,std::string propName){
    ExchangeHuafeiItem* ret = new ExchangeHuafeiItem();
    if(ret && ret->init(propId, propName)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ExchangeHuafeiItem::init(int propId,std::string propName){
    if(!Layer::init()){
        return false;
    }
    
    setItemPropId(propId);
    setPropName(propName);
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 100), 1280, 720);
    addChild(bg0);
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto dialog_bg = Sprite::create("common/dialog_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_info.png");
    title->setPosition(654,580);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ExchangeHuafeiItem::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(990, 590);
    addChild(closeMenu);
    
    showVirtualItem(propId,propName);
    return  true;
}


void ExchangeHuafeiItem::showVirtualItem(int propId,std::string propName){
    setIsVirtual(true);
    auto textInfo = Sprite::create("shop/duihuan_tianxie.png");
    textInfo->setPosition(610,480);
    addChild(textInfo);
    
    auto labe = Label::createWithSystemFont(propName,"arial",30);
    labe->setColor(Color3B::RED);
    labe->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labe->setPosition(540,480);
    addChild(labe);
    
    auto bound_phone = Sprite::create("shop/shoujihao.png");
    bound_phone->setPosition(456,365);
    addChild(bound_phone);
    
    auto input_bg_1 = Sprite::create("playerinfo/input_box_bg.png");
    input_bg_1->setPosition(720, 365);
    addChild(input_bg_1);
    _newPhoneNumber = ui::EditBox::create(Size(220, 81), ui::Scale9Sprite::create());
    _newPhoneNumber->setPosition(Point(635, 365));
    _newPhoneNumber->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
    _newPhoneNumber->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _newPhoneNumber->setTag(0);
    _newPhoneNumber->setFont("arial", 24);
    _newPhoneNumber->setDelegate(this);
    addChild(_newPhoneNumber);
    
    auto phone_hint_info1 = Sprite::create("playerinfo/phone_error_hint.png");
    phone_hint_info1->setPosition(510, 305);
    phone_hint_info1->setVisible(false);
    phone_hint_info1->setTag(1001);
    phone_hint_info1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(phone_hint_info1);
    

    
    auto hintText = Sprite::create();
    hintText->setPosition(640,230);
    if(propId<10){
        hintText->setTexture("shop/huafeicongzhi.png");
    }else{
        hintText->setTexture("shop/liuliangchongzhi.png");
    }
    addChild(hintText);
    
    auto confirm = MenuItemImage::create("shop/tijiao_1.png", "shop/tijiao_2.png",
                                         CC_CALLBACK_1(ExchangeHuafeiItem::confirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 170);
    this->addChild(confirmMenu);
}



void ExchangeHuafeiItem::confirm(Ref* ref){
    if(NULL != getChildByTag(1001) && !getChildByTag(1001)->isVisible()&&strcmp("", _newPhoneNumber->getText())!=0){
        HuafeiChangeConfirm* confirm = HuafeiChangeConfirm::create(StringUtils::format("%d",getItemPropId()),getPropName(), _newPhoneNumber->getText());
        addChild(confirm);
    }else{
        ShopHintDialog* shop = ShopHintDialog::create();
        shop->showText(ChineseWord("dialog_text_8"));
        addChild(shop);
    }
}

void ExchangeHuafeiItem::closeView(){
    removeFromParent();
}

void ExchangeHuafeiItem::editBoxEditingDidBegin(ui::EditBox* editBox){
    
    
}

void ExchangeHuafeiItem::editBoxEditingDidEnd(ui::EditBox* editBox){
    if (editBox->getTag() == 0){
        if (!StringUtil::checkPhone(editBox->getText())){
            if(NULL != getChildByTag(1001)){
                getChildByTag(1001)->setVisible(true);
            }
        }
        else{
            if(NULL != getChildByTag(1001)){
                getChildByTag(1001)->setVisible(false);
            }
        }
    }
    
}

void ExchangeHuafeiItem::editBoxTextChanged(ui::EditBox* editBox, const std::string& text){
    
    
}

void ExchangeHuafeiItem::editBoxReturn(ui::EditBox* editBox){
    
    
}

