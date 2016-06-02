//
//  ExchangeItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/1.
//
//

#include "game/mahjong/dialog/shop/ExchangeItem.hpp"
#include "game/mahjong/state/GameData.h"
#include "game/loading/Loading.h"
#include "server/NetworkManage.h"
#include "game/utils/StringUtil.h"

ExchangeItem* ExchangeItem::create(int propId,std::string propName){
    ExchangeItem* ret = new ExchangeItem();
    if(ret && ret->init(propId, propName)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ExchangeItem::init(int propId,std::string propName){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto dialog_bg = Sprite::create("shop/shop_bg_2.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_info.png");
    title->setPosition(654,630);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ExchangeItem::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    if(propId<20){
        showVirtualItem(propId,propName);
    }else{
        showRealItem(propId,propName);
    }
    return  true;
}


void ExchangeItem::showRealItem(int propId,std::string propName){
    
    auto textInfo = Sprite::create("shop/duihuan_tianxie.png");
    textInfo->setPosition(610,530);
    addChild(textInfo);
    
    auto labe = Label::create(propName,"arial",30);
    labe->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labe->setPosition(540,530);
    addChild(labe);
    
    auto bound_phone = Sprite::create("shop/lainxiren.png");
    bound_phone->setPosition(406,465);
    addChild(bound_phone);
    auto input_bg_1 = Sprite::create("shop/shuru_box_2.png");
    input_bg_1->setPosition(720, 465);
    addChild(input_bg_1);
    _lianXiRen = EditBox::create(Size(220, 81), Scale9Sprite::create());
    _lianXiRen->setPosition(Point(635, 465));
    _lianXiRen->setTag(0);
    _lianXiRen->setFont("arial", 24);
    _lianXiRen->setDelegate(this);
    addChild(_lianXiRen);
    
    auto verification = Sprite::create("shop/shoujihao2.png");
    verification->setPosition(410, 380);
    addChild(verification);
    auto input_bg_2 = Sprite::create("shop/shuru_box_2.png");
    input_bg_2->setPosition(720, 380);
    addChild(input_bg_2);
    _shouJiHao = EditBox::create(Size(230, 81), Scale9Sprite::create());
    _shouJiHao->setPosition(Point(635, 380));
    _shouJiHao->setTag(1);
    _shouJiHao->setFont("arial", 24);
    _shouJiHao->setDelegate(this);
    addChild(_shouJiHao);
 
    auto dizhi = Sprite::create("shop/xiangxidizhi.png");
    dizhi->setPosition(410, 295);
    addChild(dizhi);
    auto input_bg_3 = Sprite::create("shop/shuru_box_2.png");
    input_bg_3->setPosition(720, 295);
    addChild(input_bg_3);
    _xiangXiDiZhi = EditBox::create(Size(230, 81), Scale9Sprite::create());
    _xiangXiDiZhi->setPosition(Point(635, 295));
    _xiangXiDiZhi->setTag(1);
    _xiangXiDiZhi->setFont("arial", 24);
    _xiangXiDiZhi->setDelegate(this);
    addChild(_xiangXiDiZhi);
    
    auto hintText = Sprite::create();
    hintText->setPosition(640,230);
    hintText->setTexture("shop/yizhouneiqichu.png");
    addChild(hintText);
    
    auto confirm = MenuItemImage::create("shop/tijiao_1.png", "shop/tijiao_1.png",
                                         CC_CALLBACK_0(ExchangeItem::confirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 170);
    this->addChild(confirmMenu);

}

void ExchangeItem::showVirtualItem(int propId,std::string propName){
    
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
    _newPhoneNumber->setTag(0);
    _newPhoneNumber->setFont("arial", 24);
    _newPhoneNumber->setDelegate(this);
    addChild(_newPhoneNumber);
    
    
    password_hint_info1 = Sprite::create("register/password_simple.png");
    password_hint_info1->setPosition(510, 355);
    password_hint_info1->setVisible(false);
    password_hint_info1->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(password_hint_info1);
    password_hint_info2 = Sprite::create("register/password_not_same.png");
    password_hint_info2->setPosition(510, 245);
    password_hint_info2->setVisible(false);
    password_hint_info2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(password_hint_info2);
    
    auto verification = Sprite::create("shop/shoujihao.png");
    verification->setPosition(410, 305);
    addChild(verification);
    auto input_bg_2 = Sprite::create("shop/shuru_box_2.png");
    input_bg_2->setPosition(720, 305);
    addChild(input_bg_2);
    _confirmPhoneNumber = EditBox::create(Size(230, 81), Scale9Sprite::create());
    _confirmPhoneNumber->setPosition(Point(635, 305));
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
    
    auto confirm = MenuItemImage::create("shop/tijiao_1.png", "shop/tijiao_1.png",
                                         CC_CALLBACK_0(ExchangeItem::confirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 170);
    this->addChild(confirmMenu);
}



void ExchangeItem::confirm(){


}

void ExchangeItem::closeView(){
    removeFromParent();
}

void ExchangeItem::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){
    
    
}

void ExchangeItem::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
//    if (editBox->getTag() == 1){
//        if (!checkPassword(editBox->getText())){
//            password_hint_info1->setVisible(true);
//        }
//        else{
//            password_hint_info1->setVisible(false);
//        }
//    }
//    else if (editBox->getTag() == 2){
//        std::string passwrod1 = _newPassword->getText();
//        std::string passwrod2 = _confirmPassword->getText();
//        if (passwrod1 != passwrod2){
//            password_hint_info2->setVisible(true);
//        }
//        else{
//            password_hint_info2->setVisible(false);
//        }
//    }
}

void ExchangeItem::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}

void ExchangeItem::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}

