//
//  HintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "mahjong/bill/fpdialog/FupanDialog.hpp"

bool FupanDialog::init(){
    if(!Layer::init()){
        return false;
    }

    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    addChild(menu1);
    
    auto dialogBg = Sprite::create("common/dialog_bg_small.png");
    dialogBg->setPosition(640, 360);
    addChild(dialogBg);
    
    auto fupantext = Sprite::create("bill/shuru_fupan_hao.png");
    fupantext->setPosition(550, 420);
    addChild(fupantext);
    
    auto input_bg = Sprite::create("bill/shuru_kuang_bg.png");
    input_bg->setPosition(640, 340);
    addChild(input_bg);
    
    auto _editName = ui::EditBox::create(Size(437, 81), ui::Scale9Sprite::create());
    _editName->setPosition(Point(640, 340));
    _editName->setTag(0);
    _editName->setFont("arial", 24);
    _editName->setInputMode(ui::EditBox::InputMode::ANY);
    _editName->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    _editName->setDelegate(this);
    addChild(_editName);

    
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FupanDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(860, 490);
    closeMenu->setTag(102);
    addChild(closeMenu);
    
    return true;
}

void FupanDialog::closeView(){
    removeFromParent();
}

void FupanDialog::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){

    
}

void FupanDialog::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){
    
}

void FupanDialog::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text){
    
    
}

void FupanDialog::editBoxReturn(cocos2d::extension::EditBox* editBox){
    
    
}
