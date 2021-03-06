//
//  ExchangeItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/1.
//
//

#include "mahjong/lobby/shop/mall/ExchangeItem.hpp"
#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/utils/StringUtil.h"
#include "server/NetworkManage.h"
#include "mahjong/common/utils/Chinese.h"


ExchangeItem* ExchangeItem::create(int propId,std::string propName,std::string proptype){
    ExchangeItem* ret = new ExchangeItem();
    if(ret && ret->init(propId, propName,proptype)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ExchangeItem::init(int propId,std::string propName,std::string proptype){
    if(!Layer::init()){
        return false;
    }
    setItemPropId(propId);
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
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ExchangeItem::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    //    if(proptype == "3"){
    //        showRealItem(propId,propName);
    //    }else{
    showVirtualItem(propId,propName);
    //    }
    return  true;
}


//void ExchangeItem::showRealItem(int propId,std::string propName){
//    setIsVirtual(false);
//    auto textInfo = Sprite::create("shop/duihuan_tianxie.png");
//    textInfo->setPosition(610,530);
//    addChild(textInfo);
//
//    auto labe = Label::createWithSystemFont(propName,"arial",30);
//    labe->setAnchorPoint(Point::ANCHOR_MIDDLE);
//    labe->setPosition(540,530);
//    addChild(labe);
//
//    auto bound_phone = Sprite::create("shop/lainxiren.png");
//    bound_phone->setPosition(406,465);
//    addChild(bound_phone);
//    auto input_bg_1 = Sprite::create("shop/shuru_box_2.png");
//    input_bg_1->setPosition(720, 465);
//    addChild(input_bg_1);
//    _lianXiRen = ui::EditBox::create(Size(220, 81), ui::Scale9Sprite::create());
//    _lianXiRen->setPosition(Point(635, 465));
//    _lianXiRen->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
//    _lianXiRen->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
//    _lianXiRen->setTag(11);
//    _lianXiRen->setFont("arial", 24);
//    _lianXiRen->setDelegate(this);
//    addChild(_lianXiRen);
//
//    auto verification = Sprite::create("shop/shoujihao2.png");
//    verification->setPosition(410, 380);
//    addChild(verification);
//    auto input_bg_2 = Sprite::create("shop/shuru_box_2.png");
//    input_bg_2->setPosition(720, 380);
//    addChild(input_bg_2);
//    _shouJiHao = ui::EditBox::create(Size(230, 81), ui::Scale9Sprite::create());
//    _shouJiHao->setPosition(Point(635, 380));
//    _shouJiHao->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
//    _shouJiHao->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
//    _shouJiHao->setTag(12);
//    _shouJiHao->setFont("arial", 24);
//    _shouJiHao->setDelegate(this);
//    addChild(_shouJiHao);
//
//    auto phone_hint_info3 = Sprite::create("playerinfo/phone_error_hint.png");
//    phone_hint_info3->setPosition(600, 340);
//    phone_hint_info3->setVisible(false);
//    phone_hint_info3->setTag(1003);
//    phone_hint_info3->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    addChild(phone_hint_info3);
//
//    auto dizhi = Sprite::create("shop/xiangxidizhi.png");
//    dizhi->setPosition(410, 295);
//    addChild(dizhi);
//    auto input_bg_3 = Sprite::create("shop/shuru_box_2.png");
//    input_bg_3->setPosition(720, 295);
//    addChild(input_bg_3);
//    _xiangXiDiZhi = ui::EditBox::create(Size(230, 81), ui::Scale9Sprite::create());
//    _xiangXiDiZhi->setPosition(Point(635, 295));
//    _xiangXiDiZhi->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
//    _xiangXiDiZhi->setTag(13);
//    _xiangXiDiZhi->setFont("arial", 24);
//    _xiangXiDiZhi->setDelegate(this);
//    addChild(_xiangXiDiZhi);
//
//    auto hintText = Sprite::create();
//    hintText->setPosition(640,230);
//    hintText->setTexture("shop/yizhouneiqichu.png");
//    addChild(hintText);
//
//    auto confirm = MenuItemImage::create("shop/tijiao_1.png", "shop/tijiao_1.png",
//                                         CC_CALLBACK_1(ExchangeItem::confirm, this));
//    auto confirmMenu = Menu::create(confirm, NULL);
//    confirmMenu->setPosition(640, 170);
//    this->addChild(confirmMenu);
//
//}

void ExchangeItem::showVirtualItem(int propId,std::string propName){
    setIsVirtual(true);
    auto textInfo = Sprite::create("shop/duihuan_tianxie.png");
    textInfo->setPosition(610,510);
    addChild(textInfo);
    
    auto labe = Label::createWithSystemFont(propName,"arial",30);
    labe->setAnchorPoint(Point::ANCHOR_MIDDLE);
    labe->setColor(Color3B::RED);
    labe->setPosition(540,510);
    addChild(labe);
    
    auto bound_phone = Sprite::create("shop/shoujihao.png");
    bound_phone->setPosition(406,415);
    addChild(bound_phone);
    
    auto input_bg_1 = Sprite::create("playerinfo/input_box_bg.png");
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
    auto input_bg_2 = Sprite::create("playerinfo/input_box_bg.png");
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
                                         CC_CALLBACK_1(ExchangeItem::confirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 170);
    this->addChild(confirmMenu);
}



void ExchangeItem::confirm(Ref* ref){
    if(getIsVirtual()){
        if(NULL != getChildByTag(1001) && !getChildByTag(1001)->isVisible()&& NULL != getChildByTag(1002) && !getChildByTag(1002)->isVisible()){
            if(strcmp(_newPhoneNumber->getText(),"") != 0&&strcmp(_newPhoneNumber->getText(),_confirmPhoneNumber->getText()) == 0){
                NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getLequanChangeCommand(StringUtil::itos(getItemPropId()),_newPhoneNumber->getText(),"",""));
            }else{
                ShopHintDialog* shop = ShopHintDialog::create();
                shop->showText("请输入正确的信息!");
                addChild(shop);
                
            }
        }else{
            ShopHintDialog* shop = ShopHintDialog::create();
            shop->showText(ChineseWord("dialog_text_8"));
            addChild(shop);
        }
    }else{
        if(NULL != getChildByTag(1003) && !getChildByTag(1003)->isVisible()&&strcmp(_xiangXiDiZhi->getText(),"") != 0 && strcmp(_lianXiRen->getText(),"") != 0 && strcmp(_shouJiHao->getText(),"") != 0){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getLequanChangeCommand(StringUtil::itos(getItemPropId()),_shouJiHao->getText(),_lianXiRen->getText(),_xiangXiDiZhi->getText()));
        }else{
            ShopHintDialog* shop = ShopHintDialog::create();
            shop->showText("请输入正确的信息!");
            addChild(shop);
        }
    }
}

void ExchangeItem::closeView(){
    removeFromParent();
}

void ExchangeItem::editBoxEditingDidBegin(ui::EditBox* editBox){
    
    
}

void ExchangeItem::editBoxEditingDidEnd(ui::EditBox* editBox){
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

void ExchangeItem::editBoxTextChanged(ui::EditBox* editBox, const std::string& text){
    
    
}

void ExchangeItem::editBoxReturn(ui::EditBox* editBox){
    
    
}

