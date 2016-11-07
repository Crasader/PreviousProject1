//
//  ExchangeItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/1.
//
//

#include "game/mahjong/activities/ActivityExchange.hpp"
#include "game/mahjong/shop/ShopHintDialog.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/mahjong/loading/Loading.h"
#include "server/NetworkManage.h"
#include "game/utils/StringUtil.h"


ActivityExchange* ActivityExchange::create(int propId,std::string propName){
    ActivityExchange* ret = new ActivityExchange();
    if(ret && ret->init(propId, propName)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ActivityExchange::init(int propId,std::string propName){
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
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ActivityExchange::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
   showVirtualItem(propId,propName);
    return  true;
}




void ActivityExchange::showVirtualItem(int propId,std::string propName){
    auto textInfo = Sprite::create("shop/duihuan_tianxie.png");
    textInfo->setPosition(610,530);
    addChild(textInfo);
    
    auto labe = Label::create(propName,"arial",30);
    labe->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labe->setPosition(540,530);
    addChild(labe);
    
    auto bound_phone = Sprite::create("shop/shoujihao.png");
    bound_phone->setPosition(406,415);
    addChild(bound_phone);
    
    auto input_bg_1 = Sprite::create("shop/shuru_box_2.png");
    input_bg_1->setPosition(720, 415);
    addChild(input_bg_1);
    _newPhoneNumber = EditBox::create(Size(220, 81), Scale9Sprite::create());
    _newPhoneNumber->setPosition(Point(635, 415));
    _newPhoneNumber->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
    _newPhoneNumber->setReturnType(EditBox::KeyboardReturnType::DONE);
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
    _confirmPhoneNumber = EditBox::create(Size(230, 81), Scale9Sprite::create());
    _confirmPhoneNumber->setPosition(Point(635, 305));
    _confirmPhoneNumber->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
    _confirmPhoneNumber->setReturnType(EditBox::KeyboardReturnType::DONE);
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
                                         CC_CALLBACK_1(ActivityExchange::confirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 170);
    this->addChild(confirmMenu);
}



void ActivityExchange::confirm(Ref* ref){
    if(NULL != getChildByTag(1001) && !getChildByTag(1001)->isVisible()&& NULL != getChildByTag(1002) && !getChildByTag(1002)->isVisible()){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getActivityPrideCommand(StringUtil::itos(getItemPropId()),_newPhoneNumber->getText()));
    }else{
        ShopHintDialog* shop = ShopHintDialog::create();
        shop->showText("请输入正确的手机号");
        addChild(shop);
    }
}

void ActivityExchange::closeView(){
    removeFromParent();
}

void ActivityExchange::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
    
    
}

void ActivityExchange::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
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

void ActivityExchange::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}

void ActivityExchange::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}

