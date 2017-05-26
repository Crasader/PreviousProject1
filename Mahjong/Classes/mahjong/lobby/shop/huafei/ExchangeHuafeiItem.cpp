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
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto dialog_bg = Sprite::create("shop/shop_bg_2.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_info.png");
    title->setPosition(654,630);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ExchangeHuafeiItem::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    showVirtualItem(propId,propName);
    return  true;
}


void ExchangeHuafeiItem::showVirtualItem(int propId,std::string propName){
    setIsVirtual(true);
    auto textInfo = Sprite::create("shop/duihuan_tianxie.png");
    textInfo->setPosition(610,530);
    addChild(textInfo);
    
    auto labe = Label::createWithSystemFont(propName,"arial",30);
    labe->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labe->setPosition(540,530);
    addChild(labe);
    
    auto bound_phone = Sprite::create("shop/shoujihao.png");
    bound_phone->setPosition(406,415);
    addChild(bound_phone);
    
    auto input_bg_1 = Sprite::create("shop/shuru_box_2.png");
    input_bg_1->setPosition(720, 415);
    addChild(input_bg_1);
    _newPhoneNumber = ui::EditBox::create(Size(220, 81), ui::Scale9Sprite::create());
    _newPhoneNumber->setPosition(Point(635, 415));
    _newPhoneNumber->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
    _newPhoneNumber->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _newPhoneNumber->setTag(0);
    _newPhoneNumber->setFont("arial", 24);
    _newPhoneNumber->setDelegate(this);
    addChild(_newPhoneNumber);
    
    
    auto phone_hint_info1 = Sprite::create("playerinfo/phone_error_hint.png");
    phone_hint_info1->setPosition(510, 355);
    phone_hint_info1->setVisible(false);
    phone_hint_info1->setTag(1001);
    phone_hint_info1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(phone_hint_info1);
    
    auto phone_hint_info2 = Sprite::create("playerinfo/phone_error_hint.png");
    phone_hint_info2->setPosition(510, 255);
    phone_hint_info2->setVisible(false);
    phone_hint_info2->setTag(1002);
    phone_hint_info2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(phone_hint_info2);
    
    auto verification = Sprite::create("shop/shoujihao.png");
    verification->setPosition(410, 305);
    addChild(verification);
    auto input_bg_2 = Sprite::create("shop/shuru_box_2.png");
    input_bg_2->setPosition(720, 305);
    addChild(input_bg_2);
    _confirmPhoneNumber = ui::EditBox::create(Size(230, 81), ui::Scale9Sprite::create());
    _confirmPhoneNumber->setPosition(Point(635, 305));
    _confirmPhoneNumber->setInputMode(ui::EditBox::InputMode::PHONE_NUMBER);
    _confirmPhoneNumber->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _confirmPhoneNumber->setTag(1);
    _confirmPhoneNumber->setFont("arial", 24);
    _confirmPhoneNumber->setDelegate(this);
    addChild(_confirmPhoneNumber);
    
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
    if(NULL != getChildByTag(1001) && !getChildByTag(1001)->isVisible()&& NULL != getChildByTag(1002) && !getChildByTag(1002)->isVisible()){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getLequanChangeCommand(StringUtil::itos(getItemPropId()),_newPhoneNumber->getText(),"",""));
    }else{
        ShopHintDialog* shop = ShopHintDialog::create();
        shop->showText(ChineseWord("dialog_text_8"));
        addChild(shop);        }
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
    else if (editBox->getTag() == 1){
        std::string phone1 = _newPhoneNumber->getText();
        std::string phone2 = _confirmPhoneNumber->getText();
        if (phone1 != phone2){
            if(NULL != getChildByTag(1002)){
                getChildByTag(1002)->setVisible(true);
            }
        }
        else{
            if(NULL != getChildByTag(1002)){
                getChildByTag(1002)->setVisible(false);
            }
        }
    }else if (editBox->getTag() == 12){
        if (!StringUtil::checkPhone(editBox->getText())){
            if(NULL != getChildByTag(1003)){
                getChildByTag(1003)->setVisible(true);
            }
        }
        else{
            if(NULL != getChildByTag(1003)){
                getChildByTag(1003)->setVisible(false);
            }
        }
    }
    
}

void ExchangeHuafeiItem::editBoxTextChanged(ui::EditBox* editBox, const std::string& text){
    
    
}

void ExchangeHuafeiItem::editBoxReturn(ui::EditBox* editBox){
    
    
}

